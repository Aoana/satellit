#ifndef GSTATE_H
#define GSTATE_H

/**
 * @brief State of a game.
 */
enum gstate {
	STATE_INTRO = 0,	/**< Game is at welcome screen and where input is gathered. */
	STATE_RUNTIME,		/**< Game is running. */
	STATE_GAMEOVER,		/**< Game over. */
	STATE_VICTORY,		/**< Game finished successfully. */
	STATE_SHUTDOWN,		/**< Game set to shutdown */
};

#endif
