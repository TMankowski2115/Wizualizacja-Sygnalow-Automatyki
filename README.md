# Wizualizacja-Sygnalow-Automatyki
projekt Techniki Programowania, Politechnika Gdańska ACiR semestr 2

autorzy:
Tobiasz Mańkowski
Szymon Azarewicz

Zadania programistyczne z wizualizacją sygnałów automatyki (AiR)
(C++, z wykorzystaniem GUI w Win API, zewnętrzne dane tekstowe z czujników)

Opis pliku z danymi tekstowymi (pliki z danymi są dostępne w archiwum data.zip):
Liczby zawarte w pliku są zapisem danych wyjściowych z sensorów. Każdy sensor podaje dane z częstotliwością
25 Hz (25 linii w pliku zawiera dane wyjściowe opisujące 1 sekundę ruchu sensora). Dane są grupowane w trójki
(obejmują wskazania dotyczące każdej z 3 osi). W kolejnych kolumnach zapisane są od lewej odpowiednio:
- położenie kątowe(roll, pitch, yaw) w stopniach,
- przyspieszenie (a_x, a_y, a_z) w G (1G = 9,81m/s^2),
- wskazania magnetometru (m_x, m_y, m_z) - natężenie pola,
- wskazania żyroskopu (omega_x, omega_y, omega_z) w stopniach na sekundę.
Opis:
roll - obrót prawoskrętny względem osi X, pitch - względem osi Y, yaw - względem osi Z.
a_x - przyspieszenie sensora wzdłuż osi X sensora,
m_x - natężenie pola magnetycznego na osi X sensora,
omega_x - prędkość obrotowa względem osi X (obrót prawoskrętny względem osi X)
Początkowe próbki położenia kątowego są błędne. Algorytm wyznaczający położenie kątowe potrzebuje czasu, aby
znaleźć położenie początkowe. Należy umożliwić, aby rysowanie danych na wykresie zaczynało się od próbki
wybranej przez użytkownika (odrzucenie pierwszych n próbek).


Zrealizowane zadanie:
Zaimplementować program zawierający GUI w środowisku WinAPI, który wczytuje, przetwarza i wizualizuje
sygnał z akcelerometru umieszczonego na sprężynie robota (ruch w pionie). Program ma wyznaczyć i wyświetlać
(w GUI) przyspieszenie, prędkość, położenie sprężyny oraz współczynnik tłumienia drgań sprężyny (można
przybliżyć funkcją e^(-k), gdzie k jest współczynnikiem tłumienia). W GUI należy dodać przyciski
odpowiedzialne za wyświetlanie tych sygnałów na wykresie (należy umożliwić wyświetlanie wszystkich sygnałów
jednocześnie).
Zad 2a: outputSpring01.log
Zad 2b: outputSpring02.log
Zad 2c: outputSpring03.log
