#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <X11/Xlib.h>

static Display *dpy;

void setstatus(char *str) {
    XStoreName(dpy, DefaultRootWindow(dpy), str);
    XSync(dpy, False);
}

// int readInt(char *input) {
//     FILE *fd;
//     int val;

//     fd = fopen(input, "r");
//     if (fd==NULL)
//         return -1;
//     fscanf(fd, "%d", &val);
//     fclose(fd);
//     return val;
// }

// get download speed
// int getdownspeed(char *status, size_t size, int* last_read, int* delay) {
//     int current_total = readInt("/sys/class/net/wlp3s0/statistics/rx_bytes");
//     int speed = (current_total - *last_read) / (*delay * 1024);
//     *last_read = current_total;
//     return snprintf(status, size, " %d Kb/s ", speed);
// }

// // get upload speed
// int getupspeed(char *status, size_t size, int* last_read, int* delay) {
//     int current_total = readInt("/sys/class/net/wlp3s0/statistics/tx_bytes");
//     int speed = (current_total - *last_read) / (*delay * 1024);
//     *last_read = current_total;
//     return snprintf(status, size, " %d Kb/s ", speed);
// }

int separator(char *status, size_t size) {
    return snprintf(status, size, " • ");
}

int getdatetime(char *status, size_t size) {
    time_t result;
    struct tm *resulttm;

    result = time(NULL);
    resulttm = localtime(&result);

    return strftime(status, size, " %H.%M  ", resulttm);
}

int getbattery(char *status, size_t size) {
    FILE *fd;
    int now, full, bat;
    char stat[12];

    fd = fopen("/sys/class/power_supply/BAT0/charge_now", "r");
    fscanf(fd, "%d", &now);
    fclose(fd);

    fd = fopen("/sys/class/power_supply/BAT0/charge_full", "r");
    fscanf(fd, "%d", &full);
    fclose(fd);

    fd = fopen("/sys/class/power_supply/BAT0/status", "r");
    fscanf(fd, "%s", stat);
    fclose(fd);

    bat = 100 * now / full;
    return (strcmp(stat, "Discharging") == 0) ?
   		snprintf(status, size, " %s %d%% ", "♥", bat) :        // discharging
        snprintf(status, size, " %s %d%%+ ", "♥", bat);        // charging
}

int main(void) {
    char status[100];
    int l = 0;
    int delay = 2;
    // int last_rxread = 0;
    // int last_txread = 0;

    if (!(dpy = XOpenDisplay(NULL))) {
        fprintf(stderr, "Cannot open display.\n");
        return 1;
    }

    for (;;sleep(delay)) {
        // l = getdownspeed(status, sizeof(status) - l, &last_rxread, &delay);
        // l += getdownspeed(status + l, sizeof(status) - l, &last_txread, &delay);
        // l += separator(status + l, sizeof(status) - l);
        l = getbattery(status, sizeof(status) - l);
        l += separator(status + l, sizeof(status) - l);
        l += getdatetime(status + l, sizeof(status) - l);

        setstatus(status);
    }

    free(status);
    XCloseDisplay(dpy);

    return 0;
}
