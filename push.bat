echo 'commit message?:'
set /p msg=�������ύ��Ϣ
if not defined msg (echo "msg" not defined ) else (
echo ��������ύ��ϢΪ%msg%
git add .
git commit -m "$msg"
echo 'pushing...'
git push https://github.com/LeiYangGH/CConsole
echo 'end'
)
pause