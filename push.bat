echo 'commit message?:'
set /p msg=请输入提交信息
if not defined msg (echo "msg" not defined ) else (
echo 您输入的提交信息为%msg%
git add .
git commit -m "$msg"
echo 'pushing...'
git push https://github.com/LeiYangGH/CConsole
echo 'end'
)
pause