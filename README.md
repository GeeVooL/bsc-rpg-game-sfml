# RPG Game

Simple RPG Game written in C++11 using SFML library. Repo contains project generated by XCode, so it is Mac-only.

TODO: Game requires a lot of polishing as it was written in a hurry.

## Resources

Units textures: [Strategy Game Sprites Clip Art](http://pl.vector.me/browse/136985/strategy_game_sprites_clip_art) from [Vector.me](http://vector.me") (by MrBordello)

Grass texture: [Retro Pixelator](https://forum.unity3d.com/threads/released-free-texture-a-day-retro-pixelator-give-your-textures-that-retro-look.330649/) (by Greg-Bassett)

## Polish description

### Założenia projektu
Gra dla dwóch graczy umożliwiająca toczenie walk w trybie turowym.
Obszar gry jest kwadratem podzielonym na N x N pól.
Domyślnie zakodowany jest rozmiar 8 x 8, jednak można go bezproblemowo zmienić edytując stałą w kodzie.
Gracze mają do dyspozycji na starcie 5 oddziałów, po jednym każdego typu.
Typy jednostek to łucznik, mag, wojownik, rycerz i jeździec.
Łucznik może przemieszczać się tylko na sąsiednie pola (również pod kątem) i może atakować z dystansu. Domyślny promień ataku to 5 jednostek (okrąg jest transponowany na pola mapy).
Wojownik ma duże obrażenia i dużo punktów życia. Zasada poruszania analogiczna jak w przypadku łucznika. Zadaje obrażenia tylko sąsiednim jednostkom.
Magowie potrafią atakować na odległość i zadają obrażenia obszarowe. Obszar ataku ma kształt plusa (środek i sąsiednie pola bez tych pod kątem). Magowie nie mogą atakować, gdy w ich sąsiedztwie znajduje się inna jednostka (zarówno sojusznicza jak i wroga). Poruszają się analogicznie jak łucznicy.
Jeźdźcy poruszają się po liniach prostych. Ich domyślny zasięg ruchu to 3 jednostki. Z każdym pokonanym polem ich siłą ataku zwiększa się o 50 pkt. Atakują tylko sąsiadujące jednostki.
Rycerze są standardowymi jednostkami. Mają umiarkowaną ilość punktów życia i ataku. Poruszają się analogicznie jak łucznicy. Atakują tylko sąsiadujące jednostki.
Gra kończy się, gdy jeden z graczy straci wszystkie oddziały.

### Opis projektu
Tematem projektu jest strategia turowa dla dwóch graczy. Po uruchomieniu programu pojawia się od razu mapa z domyślnie rozmieszczonymi jednostkami. Do dyspozycji są dwie drużyny - zielona i pomarańczowa. Jednostki domyślnie zgrupowane są w oddziały, które zajmują jedno pole na mapie. W trakcie jednej tury gracz ma możliwość jednego ataku i jednego przemieszczenia oddziału zgodnie z zasadami opisanymi wyżej. Ze względu na małą ilość czasu gra jest mocno minimalistyczna i nie zawiera efektów dźwiękowych ani animacji, a grafika jest w formie elementarnej. Zostanie to poprawione w przyszłej iteracji.

### Instrukcja
Po uruchomieniu gry ukazuje się od razu mapa z domyślnie rozstawionymi jednostkami. W trakcie jednej tury graczowi przysługuje możliwość ruchu jednego oddziału oraz możliwość jednego ataku. W celu poruszenia jednostki lub zaatakowania należy najpierw zaznaczyć jednostkę. W tym celu należy na nią kliknąć lewym przyciskiem myszy. Gdy jednostka jest już zaznaczona można ją przemieścić lub zaatakować. W celu przemieszczenia jednostki należy kliknąć lewym przyciskiem myszy na jedno z pobliski pusty pól zgodnie z zasadami ruchu dla danej jednostki. Jeżeli dany ruch nie będzie możliwy jednostka wciąż pozostanie zaznaczona. Po wykonaniu ruchu jednostka jest automatycznie odznaczana i jeżeli chcemy wykonać za jej pomocą atak należy zaznaczyć ją ponownie lewym przyciskiem myszy. Można również wybrać inną jednostkę. W celu zaatakowania należy kliknąć na wybrany cel prawym przyciskiem myszy. Jeżeli atak nie jest możliwy lub, w przypadku ataków dystansowych, żadne jednostki nie otrzymują obrażeń to możliwość ataku nie jest marnowana. Po wykorzystaniu możliwości ruchu i ataku należy przekazać kontrolę kolejnemu graczowi. W tym celu należy nacisnąć lewym przyciskiem myszy przycisk „Next turn” na dolnym pasku menu. Gra kończy się, gdy jeden z graczy straci wszystkie jednostki. W dowolnym momencie można zapisać stan gry za pomocą klawisza ‚S’ oraz odczytać za pomocą klawisza ‚L’. W przypadku niepowodzenia którejkolwiek z operacji pojawi się komunikat o błędzie i grę należy zrestartować. Aby wyjść wystarczy nacisnąć przycisk X na pasku okna.
