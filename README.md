# RouteFinder

A RouteFinder plugin for Euroscope.

### Prerequisites

To install and run this you need to have [Euroscope](https://www.euroscope.hu/) installed.

### Installing

<<<<<<< HEAD
Download the latest release from [releases](https://github.com/Huijaaja42/routefinder/releases/latest).
=======
Download the latest release from [releases](/releases).
>>>>>>> 5e1bd4f2a31d2c55db00190c15bc3d8157f4bb81

Extract the contents to your Euroscope working directory e.g. `C:\%homepath%\Documents\EuroScope\`.

Every time you start Euroscope go to  `OTHER SET => Plug-ins ...` press `Load` and select the `RouteFinder.dll` from the Euroscope working directory.

Alternatively you can add `Plugins	Plugin0	RouteFinder.dll` to your `.prf` file to automatically load the plugin every time. If your `.prf` file has other plugins change `Plugin0` number accordingly e.g. `Plugin0` already exits => `Plugin1` for this plugin.

### Compiling

You need to install [Vcpkg](https://github.com/microsoft/vcpkg). Install `cpr` with `vcpkg install cpr`.

## Built With

* [Cpr](https://whoshuu.github.io/cpr/) - A Curl Wrapper
* [Vcpkg](https://github.com/microsoft/vcpkg) - A C/C++ package manager for Visual Studio

## Contributing

All contributions are welcome please submit them as pull requests to this repository.

## License

This project is licensed under the GNU GPLv3 License - see the [LICENSE](LICENSE) file for details.
