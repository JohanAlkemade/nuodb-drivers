# db-nuodb: NuoDB database bindings for Node.js #

For detailed information about this and other Node.js
database bindings visit the [Node.js db-nuodb homepage] [homepage].

## BUILDING ##

```bash
git submodule update

export PATH=/usr/local/bin:$PATH
export NODE_PATH=/usr/local/bin/node
export NUODB_INCLUDE_DIR=/Users/rbuck/tmp/nuodb-1.1.9999.macosx.x86_64/include
export NUODB_LIB_DIR=/Users/rbuck/tmp/nuodb-1.1.9999.macosx.x86_64/lib64

node-waf configure && node-waf build
```

## INSTALL ##

Before proceeding with installation, you need to have the 
[NUOCI instant client] [nci] [libraries] [nci-lib] and [include files] [nci-inc]. 
In order for the installation script to locate them properly, you'll 
need to set the NUODB_INCLUDE_DIR and NUODB_LIB_DIR environment variables. 
For example:

```bash
$ export NUODB_INCLUDE_DIR=/opt/nuodb/include
$ export NUODB_LIB_DIR=/opt/nuodb/lib64
```

Once the environment variables are set, install with npm:

```bash
$ npm install db-nuodb
```

## QUICK START ##

```javascript
var nuodb = require('db-nuodb');
new nuodb.Database({
    hostname: 'localhost',
    user: 'root',
    password: 'password',
    database: 'node'
}).connect(function(error) {
    if (error) {
        return console.log("CONNECTION ERROR: " + error);
    }

    this.query().select('*').from('users').execute(function(error, rows) {
        if (error) {
            return console.log('ERROR: ' + error);
        }
        console.log(rows.length + ' ROWS');
    });
});
```

## LICENSE ##

This module is released under the [NUODB License] [license].

Related Pages:

[homepage]: http://nodejsdb.org/db-mysql
[license]: http://www.opensource.org/licenses/mit-license.php
[nci]: http://www.oracle.com/technetwork/database/features/oci/index.html
[nci-lib]: http://www.oracle.com/technetwork/topics/linuxx86-64soft-092277.html
[nci-inc]: http://www.oracle.com/technetwork/topics/linuxx86-64soft-092277.html
