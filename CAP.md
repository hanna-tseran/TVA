###CAP теорема

Сервис будет CP, реализованный на базе MongoDB. Выбор в пользу CP сделан по нескольким причинам:

1. Большинство популярных СУБД обеспечивают устойчивость к разделению, так что это по сути выбор между A и С.
2. Выбрана согласованность данных, а не их доступность, т.к. весьма частым действием пользователя в системе может быть:
добавить тэги к видео, затем обновить страницу, чтобы увидеть, как пересчиталась общая сумма тэгов.
Неверные данные будут вводить пользователя в заблужение.
3. В общем кажется, что ни согласованность данных, ни доступность не являются критичными в данной системе,
но т.к. при реализации хотелось использовать MongoDB в силу ее простоты и популярности, а MongoDB - CP,
то выбор сделан в пользу CP сервиса.
