# Чек-лист рефакторинга Minesweeper

> Ветка: **`cleanup`** (создана от `master`).
> Источник задач: [PLAN.md](PLAN.md), [ANALYSIS.md](ANALYSIS.md).

## Окружение и правила работы

- **ОС:** Windows 11.
- **Тулчейн:** Visual Studio 2026 — все команды выполняются в **Developer PowerShell for VS 2026**
  (там доступны `cmake`, `cl`, генераторы VS/Ninja и переменные окружения SDK).
- **SFML 2.5.1:** через vcpkg (`vcpkg install sfml`) либо распакованный архив с
  `-DSFML_ROOT=<path>`. Путь к toolchain vcpkg указывается в команде конфигурации.
- **Коммиты:** каждое крупное изменение — отдельный коммит. Сообщения **простые и по сути**
  (`fix: ...`, `refactor: ...`, `test: ...`, `build: ...`, `docs: ...`); стиль и историю
  коммитов **до** рефакторинга не копировать.
- **Правило перехода к следующему пункту:** проект собирается без ошибок, а с этапа 2 — ещё и
  тесты зелёные.

### Базовые команды (Developer PowerShell for VS 2026)

```powershell
# Конфигурация (vcpkg)
cmake -B build -DCMAKE_TOOLCHAIN_FILE="<path-to-vcpkg>/scripts/buildsystems/vcpkg.cmake"

# Сборка
cmake --build build

# Запуск
.\build\Debug\minesweeper.exe    # или .\build\minesweeper.exe в зависимости от генератора

# Тесты (после этапа 2)
ctest --test-dir build --output-on-failure
```

---

## Этап 0. Подготовка

- [ ] Ветка `cleanup` создана от `master`. *(сделано)*
- [ ] Зафиксировать стартовую сборку: проект конфигурируется и собирается из чистой `build/`.
- [ ] `CMakeLists.txt`:
  - [ ] убрать дублирующийся `find_package(SFML ...)`, оставить один с компонентами
        `system window graphics`;
  - [ ] линковать только `sfml-system sfml-window sfml-graphics`;
  - [ ] заменить `\\_Resources\\` на `/` в `file(COPY ...)`;
  - [ ] убрать жёсткий `set(CMAKE_BUILD_TYPE Debug)`.
- [ ] Добавить `.gitignore` для `build/` (если ещё не игнорируется).
- [ ] **Коммит:** `build: clean up CMake config and ignore build dir`

---

## Этап 1. Критические баги

- [ ] **B1** — `GameState::handleInput()`:
  - [ ] расставить `break;` во всех `case`;
  - [ ] читать `event.mouseMove` в `MouseMoved`, `event.mouseButton` — только в кнопочных событиях;
  - [ ] проверка вручную: движение мыши к левому краю поля **не** открывает/помечает клетки.
  - [ ] **Коммит:** `fix: correct switch fall-through and event union access in input handling`
- [ ] **B2** — инициализация полей:
  - [ ] `StateManager`: `_isRemoving/_isAdding/_isReplacing = false`;
  - [ ] `GameState`: `mNeedToUpdate/mCellsRevealed/mMinesCount/mGameTime`.
  - [ ] **Коммит:** `fix: initialize StateManager and GameState members`
- [ ] **B5** — безопасный парсинг ввода в `CustomDifficultyState` (`try/catch` или `from_chars`).
  - [ ] **Коммит:** `fix: guard numeric input parsing in custom difficulty`
- [ ] **Q5** — строгая загрузка ассетов: единое логирование/исключение вместо падения на
      `getTexture`.
  - [ ] **Коммит:** `fix: fail fast with clear error on missing assets`
- [ ] Ручной прогон: все режимы, сценарии победы/проигрыша/сброса — без падений.

---

## Этап 2. Выделение игровой логики + тесты

- [ ] Создать класс **`Board`** (без зависимостей от SFML):
  - [ ] хранение размеров, числа мин, состояния клеток (`enum class`/структура, без битовой
        упаковки в `int` — **Q2**);
  - [ ] `placeMines(firstClick)` на `<random>` (**Q4**); первая клетка безопасна (**L2** — оставить
        как есть, задокументировать);
  - [ ] `reveal(x, y)` — **итеративный** flood fill (**B3**, без рекурсии);
  - [ ] `toggleMark(x, y)`, `minesLeft()`, `isWin()`, доступ к состоянию клетки;
  - [ ] **L3** — реализовать «аккорд»: открытие непомеченных соседей при совпадении числа флагов,
        проигрыш при неверном флаге;
  - [ ] **L4** — полный сброс состояния в `reset()`/конструкторе;
  - [ ] **L5** — правило отрицательного счётчика мин вынести в именованную константу/политику.
  - [ ] **Коммит:** `refactor: extract pure game logic into Board class`
- [ ] Перевести `GameState` на использование `Board` (только ввод + рендеринг):
  - [ ] **L1** — починить условие визуализации победы в `updateGridCellsOnWin`.
  - [ ] **Коммит:** `refactor: use Board in GameState; fix win rendering`
- [ ] Подключить тест-фреймворк (Catch2 или GoogleTest) через `FetchContent` + `enable_testing()`.
  - [ ] **Коммит:** `build: add test framework via FetchContent`
- [ ] Тесты на `Board`:
  - [ ] ровно N мин; первая клетка никогда не мина (L2);
  - [ ] корректность чисел-соседей;
  - [ ] flood fill раскрывает связную пустую область и её границу; рекурсии нет (B3);
  - [ ] флаг/вопрос и баланс счётчика мин (L5);
  - [ ] аккорд: верное число флагов открывает соседей, неверный флаг → проигрыш (L3);
  - [ ] условие победы; повторный `reset()` не оставляет старого состояния (L4).
  - [ ] **Коммит:** `test: cover Board logic (mines, flood fill, chord, win, reset)`
- [ ] `ctest` зелёный; визуально игра ведёт себя корректно.

---

## Этап 3. Окно и состояния

- [ ] **B4** — окно `sf::RenderWindow` создаётся один раз в `MineSweeper`; состояния меняют размер
      (`setSize`) и при необходимости `sf::View`, без пересоздания окна.
  - [ ] **Коммит:** `refactor: create window once and resize per state`
- [ ] **A2** — определиться со `StateManager`: полноценный push/pop с `Pause()/Resume()` **или**
      упрощение до модели «текущий экран» + фабрика экранов.
  - [ ] **Коммит:** `refactor: simplify state management`
- [ ] **A3** — заменить `[&]` на `[this]` во всех колбэках состояний.
  - [ ] **Коммит:** `refactor: capture this explicitly in state callbacks`
- [ ] Проверка: переходы между экранами без мерцания, навигация «назад» ожидаема.

---

## Этап 4. Чистка дубликатов и мёртвого кода

- [ ] **A4** — вынести построение типовых кнопок (`mainMenu`, `exit`) и фона в helper/фабрику;
      переиспользовать в четырёх состояниях.
  - [ ] **Коммит:** `refactor: extract shared menu/exit/background widgets`
- [ ] **A4** — общий базовый класс для «статичных» виджетов (`Background`, `Indicator`).
  - [ ] **Коммит:** `refactor: share boilerplate for static widgets`
- [ ] **Q6** — удалить мёртвый код: закомментированный `GameField`, `Pause/Resume`,
      `Container::mSelectedChild`, дублирующую загрузку `tiles.png`.
  - [ ] **Коммит:** `refactor: remove dead code and unused fields`
- [ ] **Q6** — заменить магические числа (`mMinesCount > -5`, лишний `std::ceil`, смещения текста)
      на именованные константы/корректные выражения.
  - [ ] **Коммит:** `refactor: replace magic numbers with named constants`

---

## Этап 5. Косметика и константы

- [ ] **Q2/Q3** — `#define` из `DEFINITIONS.h` → `enum class`/`constexpr`; убрать `;` внутри
      макросов сложностей; убрать повторный `SQUARE_SIZE` в `SmileButton.cpp`.
  - [ ] **Коммит:** `refactor: replace macros with typed constants`
- [ ] **Q1** — единый нейминг: методы `camelCase`, поля с префиксом `m`; `LoadFont/GetFont` →
      `loadFont/getFont`; `_data` → `mData`.
  - [ ] **Коммит:** `refactor: unify naming conventions`
- [ ] **Q7** — все комментарии на одном языке (английский).
  - [ ] **Коммит:** `docs: translate comments to English`

---

## Этап 6. Инфраструктура

- [ ] **C2** — резолвить путь к ресурсам относительно исполняемого файла.
  - [ ] **Коммит:** `fix: resolve asset paths relative to executable`
- [ ] CI (GitHub Actions, Windows + MSVC): конфигурация, сборка, `ctest` на push/PR.
  - [ ] **Коммит:** `ci: build and test on Windows`
- [ ] Обновить `README.md`: раздел архитектуры, корректный URL репозитория, запуск тестов.
  - [ ] **Коммит:** `docs: update README with architecture and test instructions`

---

## Финал

- [ ] Все этапы отмечены; `ctest` зелёный; игра работает во всех режимах.
- [ ] Открыть PR `cleanup` → `master`.

## Карта «проблема → этап»

| Проблема | Этап |
|---|---|
| B1, B2, B5, Q5 | 1 |
| A1, B3, Q2, Q4, L1, L3, L4, L5 + тесты | 2 |
| L2 (документирование) | 2 |
| B4, A2, A3 | 3 |
| A4, Q6 | 4 |
| Q1, Q2, Q3, Q7 | 5 |
| C1 | 0 |
| C2, CI, README | 6 |
