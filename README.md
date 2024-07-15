# ConsoleChat_Logger
Этот проект представляет собой чат-приложение с функциональностью логирования сообщений. Реализован класс Logger, через который проходит вся работа с файлом логов. Логи сохраняются в файл на диске, который называется log.txt.

При создании объекта логгера производится открытие файла, а при его разрушении — закрытие файла, что соответствует концепту RAII (Resource Acquisition Is Initialization).

Функциональность
В классе Logger реализованы два метода:

1)Запись строки логов в файл (writeLog):
Потокобезопасный метод для записи сообщений в файл.
Использует std::unique_lock и std::shared_mutex для предотвращения гонок данных и взаимоблокировок.

2)Чтение последней строки из файла (readLog):
Потокобезопасный метод для чтения последнего сообщения из файла.
Использует std::shared_lock и std::shared_mutex для безопасного доступа к файлу.

Потокобезопасность
Для защиты разделяемых данных и обеспечения потокобезопасности используется std::shared_mutex.

При записи лога используется std::unique_lock, чтобы обеспечить эксклюзивный доступ к файлу и предотвратить гонки данных.
При чтении лога используется std::shared_lock, чтобы позволить одновременное чтение из файла несколькими потоками, но предотвращать запись во время чтения.
