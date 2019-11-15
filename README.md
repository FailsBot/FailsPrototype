# FailsBot
This is some parts of new @FailsBot.

# Compiling

## Conan

If you want to install the project dependencies using the [Conan][conan] package
manager, then first make sure you've added the Bincrafters repository to your
configuration:

```console
$ conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
```

After that, install the dependencies:

```console
$ cd build
$ conan install .. --build missing
```

## CMake

After installing all the dependencies, build the project using [CMake][cmake]:

```console
$ cd build
$ cmake .. -G [generator]
```

Then use the generated project definition to build the project. E.g. on Windows:

```console
$ cd build
$ cmake .. -G "Visual Studio 15 2017 Win64"
$ cmake --build .
```

# Features (for developers)
* CMake;
* Conan!

# What you won't see here
* Good and stable code;
* Normal architecture (but if it will be, I will contribute to another library);
* Normal docs (if it will be, I remove that paragraph);
* Good code style.

# Project structure

    +---+-src/       - contains subfolders and bot's entry point.
        +---tgbotlib - bot network API.
        +---plugins  - all plugins and command handlers.
        +---cfg      - configs (bot key, known IDs, etc)

[cmake]: https://cmake.org/
[conan]: http://conan.io/
