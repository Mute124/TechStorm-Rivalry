 get ODE from https://bitbucket.org/odedevs/ode/downloads/
 
 extract ode 0.16.3 into the main directory of this project
 
 I'd suggest building it with this configuration
 ./configure --enable-ou --enable-libccd --with-box-cylinder=libccd --with-drawstuff=none --disable-demos --with-libccd=internal
 
 and run make, you should then be set to compile this project
