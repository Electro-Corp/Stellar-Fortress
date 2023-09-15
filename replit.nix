{ pkgs }: {
    deps = [
        pkgs.busybox
        pkgs.nano
        pkgs.sudo
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
        pkgs.SDL_image
        pkgs.imagemagick
        pkgs.SDL2_ttf
        pkgs.SDL_ttf
        pkgs.xterm
        pkgs.SDL2_mixer
    ];
}