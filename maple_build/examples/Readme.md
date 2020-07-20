[//]: # (Copyright (C) [2020] Futurewei Technologies, Inc. All rights reverved.)
[//]: # ( )
[//]: # (Licensed under the Mulan Permissive Software License v2)
[//]: # (You can use this software according to the terms and conditions of the MulanPSL - 2.0.)
[//]: # (You may obtain a copy of MulanPSL - 2.0 at:)
[//]: # ( )
[//]: # (  https://opensource.org/licenses/MulanPSL-2.0)
[//]: # ( )
[//]: # (THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER)
[//]: # (EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR)
[//]: # (FIT FOR A PARTICULAR PURPOSE.)
[//]: # (See the MulanPSL - 2.0 for more details.)
[//]: # ( )

cd HelloWorld

# .java -> .s
$MAPLE_BUILD_TOOLS/java2asm.sh HelloWorld.java

# .s -> .so
$MAPLE_BUILD_TOOLS/asm2so.sh HelloWorld.s

# run
$MAPLE_BUILD_TOOLS/run-app.sh -classpath ./HelloWorld.so HelloWorld
 
