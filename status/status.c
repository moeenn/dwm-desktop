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

int readInt(char *input) {
    FILE *fd;
    int val;

    fd = fopen(input, "r");
    if (fd==NULL)
        return -1;
    fscanf(fd, "%d", &val);
    fclose(fd);
    return val;
}

int separator(char *status, size_t size) {
    return snprintf(status, size, " • ");
}

int getdatetime(char *status, size_t size) {
    time_t result;
    struct tm *resulttm;

    result = time(NULL);
    resulttm = localtime(&result);

    return strftime(status, size, " %H.%M ", resulttm);
}

int getbattery(char *status, size_t size) {
    FILE *fd;
    int now, full, bat;
    // char stat[12];

    fd = fopen("/sys/class/power_supply/BAT0/charge_now", "r");
    fscanf(fd, "%d", &now);
    fclose(fd);

    fd = fopen("/sys/class/power_supply/BAT0/charge_full", "r");
    fscanf(fd, "%d", &full);
    fclose(fd);

    // fd = fopen("/sys/class/power_supply/BAT0/status", "r");
    // fscanf(fd, "%s", stat);
    // fclose(fd);

    bat = 100 * now / full;
   	return snprintf(status, size, " %s %d%% ", "♥", bat);
}

int main(void) {
    char status[100];
    int l = 0;

    if (!(dpy = XOpenDisplay(NULL))) {
        fprintf(stderr, "Cannot open display.\n");
        return 1;
    }

    for (;;sleep(2)) {
        l = getbattery(status, sizeof(status) - l);
        l += separator(status + l, sizeof(status) - l);
        l += getdatetime(status + l, sizeof(status) - l);

        setstatus(status);
    }

    free(status);
    XCloseDisplay(dpy);

    return 0;
}
