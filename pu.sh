#!/bin/sh
echo 'commit message?:'
read msg
if [ -z $msg ]
then
echo 'msg should not be empty'
else
git add .
git commit -m "$msg"
echo 'pushing...'
git push
fi
echo 'end'
