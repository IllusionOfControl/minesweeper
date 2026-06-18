# Журнал изменений рефакторинга

> Маппинг «проблема (из [ANALYSIS.md](ANALYSIS.md)) → решение → коммит» по ветке `cleanup`.
> Хеши коммитов указаны короткой формой.

## Проблема → решение → коммит

| ID | Проблема | Решение | Коммит |
|---|---|---|---|
| C1 | Дубли/мусор в `CMakeLists.txt`, хардкод `Debug` | Единый `find_package`, нужные компоненты, C++17, `.gitignore` | `092e296` |
| B1 | Fall-through в `switch` + чтение чужого члена `union` | `break` в каждом `case`, корректные члены событий | `130c093` |
| B2 | Неинициализированные поля (UB) | Инициализация в `StateManager` и `GameState` | `d8f842d` |
| B5 | Незащищённый `std::stoi` | Хелпер `tryParseInt` с `try/catch` | `cbbcffd` |
| Q5 | Тихий сбой загрузки ассетов → падение | Исключение с сообщением + перехват в `main` | `9588dd0` |
| A1 | Смешение логики и отрисовки | Выделен класс `Board`; `GameState` — только UI | `360ff09` |
| B3 | Рекурсивный flood fill | Итеративный обход (`std::stack`) | `360ff09` |
| L1 | Мёртвое условие визуализации победы | Переписано в `tileForCell` (ветка `Won`) | `360ff09` |
| L3 | Нерабочий «аккорд» | Реализован `Board::chord` (средняя кнопка) | `360ff09` |
| L4 | `reset()` не очищал модель | Полный сброс в `Board::reset()` | `360ff09` |
| L5 | Счётчик мин с магическим дном `-5` | Убрано; `minesLeft()` без искусственного предела | `360ff09` |
| Q2 | Битовая упаковка состояния клетки | `struct Cell` + `enum class` | `360ff09`, `0077205` |
| Q4 | `rand()` | `std::mt19937` | `360ff09` |
| L2 | Безопасна только первая клетка | Оставлено осознанно, задокументировано в `Board.hpp` | `360ff09` |
| — | Нет тестов | Catch2 (`FetchContent`) + тесты `Board` | `87dcc4d` |
| B4 | Пересоздание окна на каждом экране | `resizeWindow()` (один раз создаётся в `MineSweeper`) | `3be7aca` |
| A3 | Захват `[&]` в колбэках | Заменено на `[this]` | `b38798e` |
| A2 | Неясная модель `StateManager` | Стек (replace/push/pop) задокументирован + тесты | `9f3705e` |
| A4 | Дублирование сборки кнопок/фона | `gui/WidgetFactory` | `49bed7c` |
| A4 | Boilerplate в `Background`/`Indicator` | Базовый `PassiveComponent` | `280f83c` |
| Q6 | Мёртвый код / неиспользуемые поля | Удалены `mSelectedChild`, мёртвые текстуры, `srand` | `fa7709f` |
| Q6 | Магические числа | Именованные `constexpr` (`Input`, `Indicator`) | `0388434` |
| Q2/Q3 | `#define`, висячие `;` в макросах сложностей | `constexpr`, пресеты как `constexpr DifficultyData` | `0077205` |
| Q1 | Непоследовательный нейминг | `loadFont/getFont`, `_data → mData` | `0bfb6c5` |
| Q7 | Смешение языков в комментариях | Английский (русские удалены ранее) | — (проверено) |
| C2 | Пути к ресурсам зависят от CWD | CWD → папка exe; ресурсы рядом с бинарником | `d560608` |
| CI | Нет CI | GitHub Actions (Windows + vcpkg + `ctest`) | `989beb5` |
| README | Плейсхолдер-URL, нет архитектуры | Обновлён README | `97ea4cd` |

## Теги этапов

| Тег | Коммит | Этап |
|---|---|---|
| `stage-0` | `092e296` | Сборка |
| `stage-1` | `fd3e968` | Критические баги |
| `stage-2` | `de95e42` | `Board` + тесты |
| `stage-3` | `0bcf1c3` | Окно и состояния |
| `stage-4` | `272d495` | Чистка дубликатов |
| `stage-5` | `d407574` | Константы и нейминг |
| `stage-6` | `f29ca75` | Инфраструктура |

## Полный список коммитов (старые → новые)

```
a7251bd docs: add project analysis, plan and refactoring checklist
092e296 build: clean up CMake config and ignore build dir
130c093 fix: correct switch fall-through and event union access in input handling
d8f842d fix: initialize StateManager and GameState members
cbbcffd fix: guard numeric input parsing in custom difficulty
9588dd0 fix: fail fast with clear error on missing assets
fd3e968 docs: check off stage 0 and stage 1 in refactoring checklist
360ff09 refactor: extract pure game logic into Board class
87dcc4d test: add Catch2 suite covering Board logic
de95e42 docs: check off stage 2 in refactoring checklist
3be7aca refactor: create window once and resize per state
b38798e refactor: capture this explicitly in state callbacks
9f3705e refactor: clean up StateManager and cover it with tests
0bcf1c3 docs: check off stage 3 and record stage tags
49bed7c refactor: extract shared menu/exit/background widgets
280f83c refactor: share boilerplate for static widgets
fa7709f refactor: remove dead code and unused fields
0388434 refactor: replace magic numbers with named constants
272d495 docs: check off stage 4 in refactoring checklist
0077205 refactor: replace macros with typed constants
0bfb6c5 refactor: unify naming conventions
d407574 docs: check off stage 5 in refactoring checklist
d560608 fix: resolve asset paths relative to executable
989beb5 ci: build and test on Windows
97ea4cd docs: update README with architecture and test instructions
f29ca75 docs: check off stage 6 in refactoring checklist
```
