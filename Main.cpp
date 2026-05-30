#include "Game.hpp"
#include "Inscryption.hpp"

int main()
{
	unsigned short choice = 0;

	std::cout << "Which one? \n\nInscryption new logic: Press 1\nInscryption old logic: Press 2\n" << std::endl;
	std::cin >> choice;

	if (choice == 1)
	{
		//New system in-development:
		Game game;
		game.Run();
	}
	else if (choice == 2)
	{
		//old system:
		auto Inscryption = std::make_shared<InscryptionGame>();
		Inscryption->GameLoop();
	}
}