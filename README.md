# RouteFinder

A RouteFinder plugin for Euroscope.

### Prerequisites

To install and run this you need to have [Euroscope](https://www.euroscope.hu/) installed. And you need an API KEY from [here](https://routefinder-61e37.web.app/).

### Installing

Download the latest release from [releases](https://github.com/Huijaaja42/routefinder/releases/latest).

Extract the contents to your Euroscope working directory e.g. `C:\%homepath%\Documents\EuroScope\`.

Get your API KEY.

Create a `key.txt` file in your Euroscope working directory and put your API KEY in it.

Every time you start Euroscope go to  `OTHER SET => Plug-ins ...` press `Load` and select the `RouteFinder.dll` from the Euroscope working directory.

Alternatively, you can add `Plugins	Plugin0	RouteFinder.dll` to your `.prf` file to automatically load the plugin every time. If your `.prf` file has other plugins change `Plugin0` number accordingly e.g. `Plugin0` already exits => `Plugin1` for this plugin.

### Usage

`ADEP` is the departure airfield ICAO code.

`ADEP` is the arrival airfield ICAO code.

`FLXXX` is the planned cruise flight level where XXX is a whole number with 2 to 3 digits.

`CALLSIGN` is the callsign of any aircraft with a flight plan.

There are three ways to generate a route:

1. `.route ADEP ADES FLXXX` then press enter
2. `.route CALLSIGN` then press enter
3. `.route` select an aircraft then press enter

After a successful request, the route or the appropriate error is sent to you as a text message. All responses are also sent to your clipboard to enable easy pasting of the route.

### Compiling

You need to install [Vcpkg](https://github.com/microsoft/vcpkg). Install `cpr` and `rapidjson`  with `vcpkg install cpr rapidjson`.

## Built With

* [Cpr](https://whoshuu.github.io/cpr/) - A Curl Wrapper
* [RapidJSON](http://rapidjson.org/) - A JSON Parser
* [Vcpkg](https://github.com/microsoft/vcpkg) - A C/C++ package manager for Visual Studio

## Contributing

All contributions are welcome please submit them as pull requests to this repository.

## License

This project is licensed under the GNU GPLv3 License - see the [LICENSE](LICENSE) file for details.
