﻿
/*
     ██╗  ██╗  █████╗  ████████╗  █████╗  ███╗   ██╗  █████╗ 
	 ██║ ██╔╝ ██╔══██╗ ╚══██╔══╝ ██╔══██╗ ████╗  ██║ ██╔══██╗
	 █████╔╝  ███████║    ██║    ███████║ ██╔██╗ ██║ ███████║
	 ██╔═██╗  ██╔══██║    ██║    ██╔══██║ ██║╚██╗██║ ██╔══██║
	 ██║  ██╗ ██║  ██║    ██║    ██║  ██║ ██║ ╚████║ ██║  ██║
	 ╚═╝  ╚═╝ ╚═╝  ╚═╝/\  ╚═╝    ╚═╝  ╚═╝ ╚═╝  ╚═══╝ ╚═╝  ╚═╝
   /vvvvvvvvvvvvvvvvvvv \=========================================,
   `^^^^^^^^^^^^^^^^^^^ /---------------------------------------"
        Katana Engine \/ © 2012 - Shuriken Studios LLC
			    http://www.shurikenstudios.com
*/

#pragma once

namespace KatanaEngine
{
	/** @brief Base class for all games. Provides graphics initialization, game loop, and rendering code. 
		Inherit from this class when creating your own game. */
	class Game
	{

	public:

		Game();
		virtual ~Game();

		/** @brief Runs the game instance.
			@return Error code for exit status. */
		virtual int Run();


		/** @brief Gets the screen width in pixels.
			@return The width in pixels. */
		static int GetScreenWidth() { return s_screenWidth; }

		/** @brief Gets the screen width in pixels.
			@return The width in pixels. */
		static int GetScreenHeight() { return s_screenHeight; }

		/* Add points when an enemy dies. */
		static void AddPoints(int pts);

		/* Switch the score visibility. */
		static void ChangeScoreboardVisibility();

		/** @brief Gets the screen size in pixels.
			@return A Point representing the width and height of the screen. */
		static Vector2 GetScreenCenter() { return (Vector2(s_screenWidth / 2, s_screenHeight / 2)); }

		/** @brief Gets the name of the game.
			@return The name of the game. */
		virtual std::string GetName() const = 0;

		/** @brief Gets a pointer to the ResourceManager, for loading and managing resources.
			@return A pointer to the game's ResourceManager instance. */
		virtual ResourceManager *GetResourceManager() const { return m_pResourceManager; }

		/** @brief Gets a pointer to the ScreenManager, for managing game screens.
			@return A pointer to the game's ScreenManager instance. */
		virtual ScreenManager *GetScreenManager() const { return m_pScreenManager; }

		/** @brief Gets a pointer to the SpriteBatch, for rendering.
			@return A pointer to the game's SpriteBatch instance. */
		virtual SpriteBatch *GetSpriteBatch() const { return m_pSpriteBatch; }

		/** @brief Called when resources need to be loaded.
			@param resourceManager A reference to the game's resource manager,
			used for loading and managing game assets (resources). */
		virtual void LoadContent(ResourceManager& resourceManager) { }

		/** @brief Called when resources need to be unloaded. Override this method to unload
			any game-specific resources. */
		virtual void UnloadContent() { }

		/** @brief Called when the game has determined that game logic needs to be processed.
			@param gameTime A reference to the game time object. */
		virtual void Update(const GameTime& gameTime);

		/** @brief Called when the game determines it is time to draw a frame.
			@param spriteBatch A reference to the game's sprite batch, used for rendering. */
		virtual void Draw(SpriteBatch& spriteBatch);

		/** @brief Quits the game. */
		virtual void Quit() { m_isRunning = false; }


	protected:

		/** @brief Sets the screen resolution.
			@param width The width of the screen in pixels.
			@param height The height of the screen in pixels. */
		static void SetScreenResolution(int width, int height) { s_screenWidth = width; s_screenHeight = height; }

		/** @brief Sets the title of the game window.
			@param title The window title.
			@remark If the window title is not set, the game's name will be displayed in the title. */
		static void SetWindowTitle(std::string title) { s_windowTitle = title; }

		/** @brief Sets the location of the directory where the game's resources are stored.
			@param path The relative path to the resource directory. */
		virtual void SetResourceDirectory(const std::string &path) { m_pResourceManager->SetContentPath(path); }

		/** @brief Sets the target frame rate for the game.
			@param frames The target number of frames per second. */
		virtual void SetTargetFramesPerSecond(int const frames);

		/** @brief Sets the font for the frame counter.
			@param pFont A pointer to the font. */
		virtual void SetFrameCounterFont(Font *pFont) { m_pFrameCounterFont = pFont; }

		/** @brief Sets the font for the scoreboard.
			@param pFont A pointer to the font. */
		virtual void SetScoreboardFont(Font* pFont) { m_pScoreboardFont = pFont; }

		/** @brief Initializes the game's ScreenManager. */
		virtual void InitializeScreenManager() { m_pScreenManager = new ScreenManager(this); }

		/** @brief Displays the game's current frame rate. */
		virtual void DisplayFrameRate();

		/** @brief Displays the scoreboard and current game score. */
		virtual void DisplayScore();


		/** @brief Sets the game to display in fullscreen mode. */
		virtual void SetFullScreen(bool isFullScreen) { m_isFullScreen = isFullScreen; }

		/** @brief Sets the OpenGL flag, which forces OpenGL rendering. */
		virtual void SetOpenGLFlag() { m_requireOpenGL = true; }

		/** @brief Resets the game's timing values. */
		virtual void ResetGameTime() { m_pGameTime = new GameTime(); }


	private:

		static int s_screenWidth;
		static int s_screenHeight;

		static std::string s_windowTitle;
		static std::string s_contentDirectory;

		bool m_isInitialized = false;
		bool m_isRunning = false;
		bool m_isFullScreen = false;
		bool m_requireOpenGL = false;
		static bool m_scoreVisible;

		double m_targetFramesPerSecond = 0;
		double m_inverseTargetFrames = 0;
		double m_actualFramesPerSec = 0;
		double m_currentTime = 0;
		double m_previousTime = 0;
		static int m_score;
		float m_frameCounter = 0;

		GameTime *m_pGameTime = nullptr;
		InputState *m_pInput = nullptr;

		SpriteBatch *m_pSpriteBatch = nullptr;

		ScreenManager *m_pScreenManager = nullptr;
		ResourceManager *m_pResourceManager = nullptr;

		Font *m_pFrameCounterFont = nullptr;
		Font *m_pScoreboardFont = nullptr;

		bool IsRunning() const { return m_isRunning; }
	};
}