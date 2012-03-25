#include "stdafx.h"

using namespace System;
using namespace System::Reflection;
using namespace System::Runtime::CompilerServices;
using namespace System::Runtime::InteropServices;

[assembly: AssemblyCompany("NuoDB")]
[assembly: AssemblyProduct("NuoDB .NET Database Provider")]
[assembly: AssemblyCopyright("(C) NuoDB")]
[assembly: AssemblyTrademark("NuoDB")]

#if DEBUG
[assembly: AssemblyConfiguration("Debug")]
#else
[assembly: AssemblyConfiguration("Release")]
#endif //DEBUG

[assembly: AssemblyCulture("")]
[assembly: ComVisible(false)]

[assembly: AssemblyVersion("0.1.0.0")]
[assembly: AssemblyFileVersion("0.1.0.0")]

[assembly:CLSCompliantAttribute(true)];
