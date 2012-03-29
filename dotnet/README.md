# NuoDB Database Provider for the Microsoft .NET Framework #

This is the .NET database provider for [NuoDB](http://www.nuodb.com).

## License ##

Please refer to the [LICENSE](https://github.com/nuodb/nuodb-drivers/blob/master/LICENSE) provided with this
distribution.

## Requirements ##

* Microsoft Visual Studio 2010
* Microsoft .NET 3.5/4 Framework
* Windows version of NuoDB installed

## Building ##

Using VS2010, open the appropriate solution:

* **nuodb.sln** - for .NET 4
* **nuodb35.sln** - for .NET 3.5

## Known Issues ##

There is a known issue using `msclr::interop::marshal_context` when building for .NET 3.5.