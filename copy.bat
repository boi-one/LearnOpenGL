@echo off
setlocal

set "destination=x64\Debug"

copy "container.jpg"   "%destination%"
copy "shader.vert"     "%destination%"
copy "shader.frag"     "%destination%"
copy "awesomeface.png" "%destination%"
