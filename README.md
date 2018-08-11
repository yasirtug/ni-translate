BUILD INSTRUCTIONS:

qmake: qmake ni-translate.pro -spec linux-g++

Make: make in %{buildDir}

cp -n %{sourceDir}/translate.py %{buildDir}

cp -r -n %{sourceDir}/googletrans %{buildDir}

cp -n %{sourceDir}/language_list %{buildDir}
