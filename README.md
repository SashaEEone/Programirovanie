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

