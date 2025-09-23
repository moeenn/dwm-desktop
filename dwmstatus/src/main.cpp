#include <X11/Xlib.h>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <thread>

namespace config {
static constexpr std::chrono::duration sleep_duration = std::chrono::seconds(5);
static constexpr const char* time_format = "  %B %d  -  %H:%M  ";
} // namespace config

void set_status(Display* display, const std::string& status)
{
    XStoreName(display, DefaultRootWindow(display), status.c_str());
    XSync(display, false);
}

void current_time(std::string& out)
{
    auto now = std::chrono::system_clock::now();
    std::time_t time_now = std::chrono::system_clock::to_time_t(now);
    std::tm local_tm = *std::localtime(&time_now);

    std::stringstream ss;
    ss << std::put_time(&local_tm, config::time_format);
    out = ss.str();
}

int main()
{
    Display* display;
    if (!(display = XOpenDisplay(NULL))) {
        std::cerr << "error: failed to open display\n";
        return 1;
    }

    std::string time;

    while (true) {
        current_time(time);
        set_status(display, time);
        std::this_thread::sleep_for(config::sleep_duration);
    }

    XCloseDisplay(display);
    return 0;
}

/*
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
// #include <alsa/asoundlib.h>
// #include <alsa/control.h>

#define HAS_BATTERY 0

static Display *dpy;

void setstatus(char *str)
{
    XStoreName(dpy, DefaultRootWindow(dpy), str);
    XSync(dpy, False);
}

int separator(char *status, size_t size)
{
    return snprintf(status, size, " • ");
}

int getdatetime(char *status, size_t size)
{
    time_t result;
    struct tm *resulttm;

    result = time(NULL);
    resulttm = localtime(&result);

    return strftime(status, size, " %b %d, %H:%M  ", resulttm);
}

#if HAS_BATTERY == 1
int getbattery(char *status, size_t size)
{
    FILE *fd;
    int now, full, bat;
    char stat[15];

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
    return (strcmp(stat, "Discharging") == 0) ? snprintf(status, size, " %s %d%% ", "♥", bat)
                                              : snprintf(status, size, " %s %d%%+ ", "♥", bat);
}
#endif

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

int main(void)
{
    char status[100];
    int l = 0;
    int delay = 2;

    if (!(dpy = XOpenDisplay(NULL)))
    {
        fprintf(stderr, "Cannot open display.\n");
        return 1;
    }

    for (;; sleep(delay))
    {
#if HAS_BATTERY == 1
        l = getbattery(status, sizeof(status) - l);
        l += separator(status + l, sizeof(status) - l);
        l += getdatetime(status + l, sizeof(status) - l);
#else
        l += getdatetime(status, sizeof(status) - l);
#endif
        setstatus(status);
    }

    XCloseDisplay(dpy);
    return 0;
}
*/
