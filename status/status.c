#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <X11/Xlib.h>
// #include <alsa/asoundlib.h>
// #include <alsa/control.h>

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

int separator(char *status, size_t size) {
    return snprintf(status, size, " • ");
}

int getdatetime(char *status, size_t size) {
    time_t result;
    struct tm *resulttm;

    result = time(NULL);
    resulttm = localtime(&result);

    return strftime(status, size, " %b %d, %H:%M  ", resulttm);
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
    return (strcmp(stat, "Discharging") == 0) 
      ? snprintf(status, size, " %s %d%% ", "♥", bat) 
      : snprintf(status, size, " %s %d%%+ ", "♥", bat); 
}

// int
// get_vol(void)
// {
//     int vol;
//     snd_hctl_t *hctl;
//     snd_ctl_elem_id_t *id;
//     snd_ctl_elem_value_t *control;

// // To find card and subdevice: /proc/asound/, aplay -L, amixer controls
//     snd_hctl_open(&hctl, "hw:0", 0);
//     snd_hctl_load(hctl);

//     snd_ctl_elem_id_alloca(&id);
//     snd_ctl_elem_id_set_interface(id, SND_CTL_ELEM_IFACE_MIXER);

// // amixer controls
//     snd_ctl_elem_id_set_name(id, "Master Playback Volume");

//     snd_hctl_elem_t *elem = snd_hctl_find_elem(hctl, id);

//     snd_ctl_elem_value_alloca(&control);
//     snd_ctl_elem_value_set_id(control, id);

//     snd_hctl_elem_read(elem, control);
//     vol = (int)snd_ctl_elem_value_get_integer(control,0);

//     snd_hctl_close(hctl);
//     return vol;
// }

int main(void) {
    char status[100];
    int l = 0;
    int delay = 2;

    if (!(dpy = XOpenDisplay(NULL))) {
        fprintf(stderr, "Cannot open display.\n");
        return 1;
    }

    for (;;sleep(delay)) {
        l = getbattery(status, sizeof(status) - l);
        l += separator(status + l, sizeof(status) - l);
        l += getdatetime(status + l, sizeof(status) - l);

        setstatus(status);
    }

    free(status);
    XCloseDisplay(dpy);

    return 0;
}
