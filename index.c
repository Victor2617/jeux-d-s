#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define _CRA_SECURE_NO_WARNINGS

#define NUM_DICE 6
#define TARGET_SCORE 10000

		// Structure pour stocker les informations d'un joueur
		typedef struct {
			char name[50];
			int score;
		} Player;
		// Fonction pour demander le nombre de joueurs et leur nom
		int inputPlayers(Player players[]) {
			int numPlayers;
			printf("Combien de joueurs (2-6) ? ");
			scanf_s("%d", &numPlayers);
			if (numPlayers < 2 || numPlayers > 6) {
				printf("Nombre de joueurs non valide.\n");
				return 0;
			}
			for (int i = 0; i < numPlayers; i++) {
				printf("Entrez le nom du joueur %d : ", i + 1);
				scanf_s("%s", players[i].name);
				players[i].score = 0;
			}
			return numPlayers;
		}

		// Fonction pour lancer les dés et calculer les points
		int rollDice(int dice[]) {
			for (int i = 0; i < NUM_DICE; i++) {
				dice[i] = rand() % 6 + 1;
			}
			int points = 0;
			int numOnes = 0;
			int numSixes = 0;
			for (int i = 0; i < NUM_DICE; i++) {
				if (dice[i] == 1) numOnes++;
				if (dice[i] == 6) numSixes++;
				points += dice[i];
			}
			if (numOnes == NUM_DICE) return TARGET_SCORE;
			if (numSixes == NUM_DICE) return -1000;
			if (numOnes == 3 && numSixes == 3) return 600;
			if (numOnes == 3) return 1050;
			if (numSixes == 3) return 300;
			return points;
		}

		// Fonction pour afficher le nom et le score d'un joueur
		void printScore(Player player) {
			printf("%s : %d points\n", player.name, player.score);
		}

		// Fonction pour gérer le déroulement d'une partie
		void playGame(Player players[], int numPlayers) {
			int currentPlayer = 0;
			while (1) {
				printf("Au tour de %s de jouer.\n", players[currentPlayer].name);
				printf("Appuyez sur * pour lancer les dés : ");
				getchar(); // Attendre que l'utilisateur appuie sur *
				int dice[NUM_DICE];
				int points = rollDice(dice);
				if (points >= TARGET_SCORE) {
					printf("Vous avez gagné !\n");
					break;
				}
				else if
					(points < 0) {
					printf("Vous perdez 1000 points !\n");
					players[currentPlayer].score = 0;
				}
				else {
					printf("Vous avez gagné %d points.\n", points);
					players[currentPlayer].score += points;
				}
				if (players[currentPlayer].score >= TARGET_SCORE) {
					printf("%s est temporairement gagnant !\n", players[currentPlayer].name);
				}
				currentPlayer++;
				if (currentPlayer == numPlayers) currentPlayer = 0;
			}
			// Trouver le joueur qui a le plus gros score
			int winner = 0;
			for (int i = 1; i < numPlayers; i++) {
				if (players[i].score > players[winner].score) winner = i;
			}
			printf("Le gagnant est %s avec un score de %d points !\n", players[winner].name, players[winner].score);
		}

		int main() {
			srand(time(NULL)); // Initialiser la génération aléatoire
			Player players[6];
			int numPlayers = inputPlayers(players);
			if (numPlayers == 0) return 1; // Si le nombre de joueurs est invalide, quitter le programme
			playGame(players, numPlayers);
			return 0;
		}