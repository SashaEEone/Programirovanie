# Первая часть

### 1. Использую git status, чтобы определить состояние файлов 

![Команда git status](screen/1.png)

### 2. Использую git log, чтобы просмотреть историю изменения файлов

![Команда git status](screen/2.png)

### 3. Создал sort.c

![Команда git status](screen/3.png)

### 4. Как сейчас выглядит git status. P.S (я сразу стал делать add, commit и push, поэтому пропущу пункты до 9)

![Команда git status](screen/4.png)

### 9-10. Добавил комментарий с любым текстом в этот же файл, git status выглядит так

![Команда git status](screen/10.png) 
![Команда git status](screen/9.png)

### 11-12. Добавил изменения файла и посмотрел как сейчас выглядит git status

![Команда git status](screen/11-12.png) 

### 13-14-15. Изменил файл еще раз, сделал коммит, посмотрел как выглядит git status, log

![Команда git status](screen/13-14-15.png) 

### 16-17. Добавил в stage и закоммитил последнее изменение, запушил на удаленный репо

![Команда git status](screen/16-17.png) 

# Вторая часть

### 1-2-3. Добавил в stage и закоммитил последнее изменение, запушил на удаленный репо

![Команда git status](screen/18.png) 

### 4-5. В git status изменилось: On branch main or On branch mybranch, далее убедился, что нахожусь на ветке - mybranch

![Команда git status](screen/19.1.png) 
![Команда git status](screen/19.2.png) 
![Команда git status](screen/20.png) 

### 6-7. Создал file.1.txt, добавил туда свое имя и закоммитил

![Команда git status](screen/21-22.png) 

### 8. Использую git log --oneline --graph, чтобы увидеть, что моя ветка указывает на новые коммиты

![Команда git status](screen/23.png)

### 9-10. Вернулся на ветку main, использовал git log --oneline --graph, изменилось: коммит из ветки mybranch не будет виден на ветки main   

![Команда git status](screen/24-25.png)

### 11-12. Создал новый файл file2.txt, закоммитил его. Использовал git log --oneline --graph --all, чтобы увидеть, что наша ветка указывает на новый коммит, и что теперь у двух веток разные коммиты

![Команда git status](screen/26.1.png)
![Команда git status](screen/26.2.png)

### 13-14. Переходим на ветку mybranch и проверяем исчезновение file2.txt

![Команда git status](screen/27-28.png)

### 15. Используя git diff mybranch main чтобы увидеть разницу между двумя ветками.

![Команда git status](screen/29.png)


# Задание на чертверку

### 1. Переключаюсь на ветку mybranch

![Команда git switch](chetverka/chet1.png)

### 2. Перезапиcываю содержимое в sort.c

![sort.c](chetverka/chet2.png)

### 3-4. Использую git diff (смотрю, что поменялось) и git diff --staged (какие изменения в staged)

![Команда git diff](chetverka/chet3.png)
![Команда git diff --staged](chetverka/chet4.png)

### 5-7. Добавляю в staged файл sort.c, смотрю, что говорит git diff и git diff --staged

![Команда git add, diff, diff --staged](chetverka/chet5.png)

### 8-10. Удаляю любое из чисел в массиве в sort.c, смотрю, что говорит git diff и git diff --staged

![Команда git diff](chetverka/chet6.png)
![Команда git diff](chetverka/chet7.png)

### 11. Когда мы удалили число после git add, это новое изменение находится в рабочей директории, но не в staged

### 12. Использовал git status и обратил внимание, что sort.c присутствует дважды в выводе.

![Команда git status](chetverka/chet8.png)

### 13-14. Использовал git restore --staged sort.c, чтобы отменить индексацию изменения , посмотрел, что говорит git status?

![Команда git restore --staged, status](chetverka/chet9.png)

### 15-16. Индексировал изменения и сделал коммит. Посмотрел как выглядет журнал

![Команда git restore --staged, status](chetverka/chet10.png)

### 17-18. Добавил в sort.c в main() printf(“hello git\n”);. Использовал cat, чтобы посмотреть содержимое

![Команда cat](chetverka/chet11.png)

### 19-22. Использовал git status, restore sort.c

![Команда git status, restore](chetverka/chet12.png)
![Команда git status](chetverka/chet13.png)

# Вторая часть задание на чертверку

### 1. Создал файл greeting.txt, проиндексировал его и закоммитил с сообщением “Add file greeting.txt” 

![Команда git commit](chetverka/chet14.png)

### 2. Добавил в этот файл слово hello, индексировал и коммитил с текстом "Add content to greeting.txt"  

![Команда git add, commit](chetverka/chet15.png)

### 3-5. Создал ветку с именем feature/uppercase, переключ. на неё, посмотрел, что в git status

![Команда git branch, swtich, status](chetverka/chet16.png)

### 6-8. Отредактировал greeting.txt (HELLO), сделал add и commit, далее посмотрел, что выводит branch

![Команда git add, commit, branch](chetverka/chet17.png)

### 9. Посмотрел каков вывод git log --oneline --graph --all

![Команда git log --oneline --graph --all](chetverka/chet18.png)

### 10-12. Переключ. на гл. ветку, использовал cat, чтобы увидеть содерж. нашего файла и сравнил ветки

![Команда git switch, diff](chetverka/chet19.png)

### 13-14. Объед. ветки и использовал cat, чтобы увидеть содерж. файла

![Команда git merge](chetverka/chet20.png)

### 15-19. Удалил новую ветку, смержил ветку  mybranch в main, посмотрел, что выводит git log --oneline --graph --all, запушил измен. и документ
![Команда git branch -d, merge, push](chetverka/chet21.png)
