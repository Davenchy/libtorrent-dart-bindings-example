# LibTorrent Dart Bindings Tutorial

## Requirements

- Ensure libtorrent shared library is installed on your system and recognized by the compiler using the flag `-ltorrent-rasterbar`.
- If you have libtorrent source files in a custom path, update the `wrapper/Makefile` accordingly.
- [Dart SDK](https://dart.dev/get-dart)

## Makefile

- The `wrapper/Makefile` contains the following rules:

1. **debug**: Builds a test binary with gdb flag for testing.
2. **run**: Similar to `debug` but runs the binary after build.
3. **build**: Builds the wrapper library `libwrapper.so` by default.

## Build the Wrapper Library

- To build the wrapper library, execute the following command:

```sh
make build
```

## Run the Example Project

- Copy the library file `libwrapper.so` into the dart project directory.
- Then run the project:

```sh
dart run
```

## Resources

### LibTorrent

- [LibTorrent Tutorial](https://www.libtorrent.org/tutorial-ref.html)
- [Settings Pack](https://www.libtorrent.org/reference-Settings.html#settings_pack)
- [Alert Categories](https://www.libtorrent.org/reference-Alerts.html#alert-category-t)
- [Alerts](https://www.libtorrent.org/reference-Alerts.html#overview)
- [Parse Magnet URI](https://www.libtorrent.org/reference-Core.html#parse_magnet_uri())
- [Add Torrent Parameters](https://www.libtorrent.org/reference-Add_Torrent.html#add_torrent_params)
- [Session Handle](https://www.libtorrent.org/reference-Session.html#session_handle)
- [Torrent Handle](https://www.libtorrent.org/reference-Torrent_Handle.html#torrent_handle)
- [Torrent Info](https://www.libtorrent.org/reference-Torrent_Info.html#torrent_info)
- [File Storage](https://www.libtorrent.org/reference-Storage.html)

### Dart FFI

- [C interop using dart:ffi](https://dart.dev/interop/c-interop)
- [dart-lang repo ffi samples](https://github.com/dart-lang/samples/tree/main/ffi)

## Contribution

**Feel free to fork or create pull requests**
