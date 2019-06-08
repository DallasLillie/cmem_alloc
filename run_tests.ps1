# script args
param([string]$project_dir)

# run tests
# environment variables for the solution dir should be passed in as an arg to this script
& $project_dir\bin\$env:PLATFORM\$env:CONFIGURATION\pool_allocator_tests.exe --gtest_output=xml:$project_dir\tests\output\$env:PLATFORM\$env:CONFIGURATION\pool_allocator_tests.xml

# upload results to AppVeyor
$wc = New-Object 'System.Net.WebClient'
$wc.UploadFile("https://ci.appveyor.com/api/testresults/junit/$($env:APPVEYOR_JOB_ID)", (Resolve-Path $project_dir\tests\output\$env:PLATFORM\$env:CONFIGURATION\pool_allocator_tests.xml))