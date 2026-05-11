import os
import getpass # Это чтобы узнать твое имя в системе

def audit_my_repo():
    # 1. Узнаем, кто тут Босс
    user = getpass.getuser()
    
    # 2. Узнаем, где мы находимся (аналог команды pwd)
    current_dir = os.getcwd()
    
    # 3. Получаем список всех объектов в папке
    all_items = os.listdir('.')
    
    # 4. Фильтруем: оставляем только папки (директории)
    directories = [d for d in all_items if os.path.isdir(d) and not d.startswith('.')]
    
    print(f"--- ОТЧЕТ ---")
    print(f"Пользователь: {user}")
    print(f"Рабочая директория: {current_dir}")
    print(f"Всего активных проектов в корне: {len(directories)}")
    print(f"Список проектов: {', '.join(directories)}")
    print(f"------------------------------")

if __name__ == "__main__":
    audit_my_repo()
