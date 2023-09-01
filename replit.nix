{ pkgs }: {
    deps = [
        pkgs.imagemagick6_light
        pkgs.sl
        pkgs.gdb
        pkgs.jsoncpp
        pkgs.ncurses
        pkgs.libjpeg
        pkgs.SDL2
        pkgs.SDL
        pkgs.xorg.libX11
        pkgs.xorg.libXcursor
        pkgs.xorg.libXrandr
        pkgs.freetype
        pkgs.libudev-zero
        pkgs.libudev0-shim
        pkgs.udev
        pkgs.eudev
    ];
}