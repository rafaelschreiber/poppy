## POPpy 
### A minimalistic POP3 client 📫

![](https://raw.githubusercontent.com/rafaelschreiber/poppy/master/doc/img/poppy_logo.png)

## Usage 👨‍💻
```sh
$ poppy [OPTIONS] bookmark

Positionals:
  bookmark TEXT REQUIRED      Specify POP3 bookmark

Options:
  -h,--help                   Print this help message and exit
  -c,--config TEXT:FILE       Path to your config file
  -d,--debug                  Turn on debug mode
```

## Dependencies
### Program dependeices
- A C++ compiler
- [The Meson Build System](https://mesonbuild.com)
- [GnuTLS](https://www.gnutls.org/download.html)
- [protobuf](https://developers.google.com/protocol-buffers)
- [gRPC](https://grpc.io/docs/what-is-grpc/introduction) including [protoc-gen-grpc-web](https://github.com/grpc/grpc-web/releases) 
- [Envoy]() proxy
- [npm]()
- ### Library dependencies
- [GnuTLS](https://github.com/nlohmann/json)
- [GNU Mailutils](https://mailutils.org)
- [CLI11](https://github.com/CLIUtils/CLI11)
- [cpp-subprocess](https://github.com/arun11299/cpp-subprocess)
- [spdlog](https://github.com/gabime/spdlog)
- [toml++](https://github.com/marzer/tomlplusplus)

## Compilation ⚙️

**Note: Location of header-only libs must be included in meson-options.txt**
```sh
$ git clone https://github.com/rafaelschreiber/schreiber_project_2
$ cd schreiber_project_2/build
$ meson --prefix $PWD/.. .. # if an installation will be performed specify your wished installation path
$ ninja
$ meson install // only if an installation is wished. Fails if higher permissions are requiered (sudo)
$ ./poppy bookmarkname
```

Compilation was tested on the following platforms:
- macOS Big Sur (Apple clang version 12.0.0)
- Ubuntu 20.04 LTS (gcc version 9.3.0)

## Documenation 📄
A documentation is available but only in [german](https://github.com/rafaelschreiber/schreiber_project_2/blob/master/doc/main.pdf).
