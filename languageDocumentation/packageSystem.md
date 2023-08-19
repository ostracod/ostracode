
# Package System

This page documents the package system in OstraCode.

## Principles of Usage

A "package" is a directory containing an end-user application, or a library which may be imported by other packages. Each package must use the directory structure as documented on this page.

A "package registry" is a web server which serves OstraCode packages developed by various authors. Each registry is uniquely identified by its hostname, and may use a custom port and path to serve files. A hostname may not host more than one package registry.

Dependency packages are stored in the directory `~/.ostraCodePackages`. The `.ostraCodePackages` directory is organized in the following manner:

* At the top level, `.ostraCodePackages` contains one directory for each package registry.
    * The name of each registry directory is the hostname of the registry, such as `subdomain.example.com`.
* Each registry directory contains one directory for each package.
    * The name of each package directory is the name of the package, such as `myPackage`.
* Each package directory contains one directory for each version of the package.
    * The name of each version directory is the version number of the package, such as `2.5.1`.
* Each version directory contains package files and directories such as `ostraConfig.json`, `src`, etc.

A "package manager" is a local program which installs application dependencies. When installing dependencies, a package manager follows the steps below:

1. The package manager reads `ostraConfig.json` of the application package.
1. The package manager queries package registries for suitable package versions.
1. The package manager downloads package files from the registries.
1. The package manager saves the files in `~/.ostraCodePackages`.
1. The package manager updates `packageLock.json` of the application package.

After application dependencies are installed, the application can run, and `importPackage` statements will import dependency packages from `~/.ostraCodePackages`.

## Directory Structure

Each package has the directory structure below:

* `ostraConfig.json` (file) stores package metadata and the list of required dependencies.
* `packageLock.json` (file) stores the dependency version numbers which the package will use when run as an application. `packageLock.json` is updated when the package manager installs new packages. `packageLock.json` ensures that applications remain stable even if a faulty new version of a dependency is added to `~/.ostraCodePackages`.
* `src` (directory) stores OstraCode source files. Each OstraCode file has the extension `.ostc`.
* `data` (directory) stores general-purpose data used by the package during runtime.

## OstraConfig File

The content of `ostraConfig.json` has the following type:

```
dictT [fields [
    name (strT)
    version (strT)
    ostraCodeVersion (strT)
    appModule (strT) [optional]
    libModule (strT) [optional]
    registries (dictT [fieldType (
        dictT [fields [
            url (strT)
        ]]
    )]) [optional]
    dependencies (dictT [fieldType (
        dictT [fields [
            registry (strT) [optional]
            name (strT) [optional]
            minVersion (strT)
            maxVersion (strT) [optional]
        ]]
    )]) [optional]
]]
```

* `name` is the name of the package.
* `version` is the semantic version number of the package.
* `ostraCodeVersion` is the semantic version number of OstraCode with which the package is compatible.
* `appModule` defines the default entry-point module when running the package as an application. `appModule` is a path relative to the `src` directory.
* `libModule` defines the module which will be imported when using the `importPackage` statement. `libModule` is a path relative to the `src` directory.
* `registries` is a map from name to package registry.
    * `url` is the web address where the package registry responds to requests.
* `dependencies` is a map from import specifier to dependency.
    * `registry` is the name of the registry which stores the dependency. `registry` is optional if only one registry is defined in `registries`.
    * `name` is the name of the dependency known by the package registry. `name` may be excluded if the import specifier and package name are equal.
    * `minVersion` is the lowest compatible semantic version number.
    * `maxVersion` is the highest semantic version number to use. If `maxVersion` is excluded, then the package registry will provide the latest package with the same major version as `minVersion`.


