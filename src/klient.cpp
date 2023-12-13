#include "klient.hh"

int klient()
{
  // Inicjalizacja obiektów i zmiennych
  Configuration Config;             // Obiekt przechowujący konfigurację systemu
  Reader reader;                    // Obiekt do czytania danych z plików XML
  Set4LibInterfaces lib_handler;    // Klasa zarządzająca interfejsami do bibliotek dynamicznych
  AbstractInterp4Command *command;  // Wskaźnik na abstrakcyjną klasę reprezentującą aktualnie wykonywaną funkcję z biblioteki
  std::istringstream stream;        // Strumień do przetwarzania danych
  std::list<std::thread> threads; // Kontener na wątki

  // Inicjalizacja czytnika komend
  reader.init("config/commands.cmd");

  // Wczytanie pliku konfiguracyjnego
  if (!reader.ReadFile("config/config.xml", Config))
  {
    return 1;
  }

  // Inicjalizacja sceny i nawiązywanie połączenia
  Scene scene(Config);
  Sender sender(&scene);
  if (!sender.OpenConnection())
    return 1;

  // Inicjalizacja interfejsów bibliotek dynamicznych
  lib_handler.init(Config.libs);

  // Wątek do obserwacji i wysyłania danych
  std::thread Thread4Sending(&Sender::Watching_and_Sending, &sender);

  std::string key;

  // Wczytywanie poleceń z pliku
  reader.execPreprocesor(stream);
  while (stream >> key)
  {
    // Wykonanie komendy zgodnie z interfejsem
    command = lib_handler.execute(key);

    // Obsługa komend równoległych
    if (lib_handler.isParallel() && command != nullptr)
    {
      command->ReadParams(stream);
      threads.push_back(std::thread(&AbstractInterp4Command::ExecCmd, command, &scene));
    }
    // Czekanie na zakończenie wątków, jeśli komendy nie są równoległe
    else if (!lib_handler.isParallel())
    {
      for (auto & i : threads) {
        if (i.joinable())
          i.join();
      }
      // for (int i = 0; i < threads.size(); ++i)
      // {
      //   if (threads[i].joinable())
      //     threads[i].join();
      // }
      threads.clear();
    }
  }

  // Zakończenie pracy i oczekiwanie na zakończenie wątków
  sender.Send("Close\n");
  sender.CancelCountinueLooping();
  // for (int i = 0; i < threads.size(); ++i)
  // {
  //   if (threads[i].joinable())
  //     threads[i].join();
  // }
  for (auto & i : threads) {
    if (i.joinable())
      i.join();
}
  Thread4Sending.join();

  return 0;
}