4.1 Overview
One of the key features of many embedded operating systems is the ability to keep track of
time. Being able to keep track of time is useful for many things, from simply displaying it
(like most microwaves ovens) to using it to schedule operations as is needed, for example, in
other household appliances such as ovens, dishwashers and MANY others.
From working with the STM32 previously, you should already be aware that there is no
built-in means to keep track of time, besides using its own internal clock that could become
rather inaccurate after a long time. This is because the STM32 doesn’t have a built-in RTC
(real time clock), or access to the internet, and thus the NTPD (Network Time Protocol
Daemon) to fetch, set and store the date and time. There are a few ways of getting around
this issue. The first is to manually set the time when flashing the board, and then use the
available timers to keep track of the time. This, as you might expect, is not ideal: it requires
the user to manually set the time each time the board is power cycled (turned off and on) and
also requires a timer that is perpetually on. We could also add internet connectivity using
something like a WIZ5500 Ethernet Controller. However, this is a very involved process which
is beyond the scope of this course. Instead, the approach we will use is to add an external
RTC which we will interface with using I2C. The RTC also needs to be set manually, but it
has its own battery and maintains the time even if the STM32 is power cycled (as long as
you dont overwrite the time!).
Hopefully by now you should already be familiar with the concept of UNIX time, epoch time
or POSIX time and understand the benefits of using it. With that in mind, we will also write
code for converting the time we get from the RTC to an equivalent epoch timestamp (with
some adjustments to make things a bit easier).


In this practical, I will be using C to write to time to an RTC module. I will also have an
LED that will flicker on and off every second, as well as publish the time (and corresponding
epoch time) using UART to a serial monitor on your PC/Laptop.
