#include "Window.h"

Window::Window(sf::RenderWindow& m_window, const std::string& title)
{
	m_windowSize = m_window.getSize();

	/*m_windowSize.x = 2256;
	m_windowSize.y = 1504;*/
	/*m_windowSize.x = 2560;
	m_windowSize.y = 1600;*/
	m_windowSize.x = 1920;
	m_windowSize.y = 1080;

	DEFAULT_SCALE = SetDefaultScale(m_windowSize);
	DEFAULT_SCALE_X = (float)m_windowSize.x / WIDTH;
	DEFAULT_SCALE_Y = (float)m_windowSize.y / HEIGHT;
}

Window::Window() {}

void Window::SetBackground(sf::Sprite& backgroundSprite, sf::Texture& backgroundTexture, const std::string& backgroundPath)
{
	backgroundTexture.loadFromFile(backgroundPath);
	backgroundSprite.setTexture(backgroundTexture);
	sf::Vector2u currentTextureSize = backgroundTexture.getSize();

	float backgroundScaleX = (float)m_windowSize.x / currentTextureSize.x,
			backgroundScaleY = (float)m_windowSize.y / currentTextureSize.y;
	backgroundSprite.setScale(backgroundScaleX, backgroundScaleY);
}

void Window::SetTitle(sf::Sprite& titleSprite, sf::Texture& titleTexture, const std::string& titlePath)
{
	titleTexture.loadFromFile(titlePath);
	titleSprite.setTexture(titleTexture);

	float scale = DEFAULT_SCALE / 3.3F;
	titleSprite.setScale(scale, scale);

	float titleSpriteX = titleSprite.getGlobalBounds().width,
		titleSpriteY = titleSprite.getGlobalBounds().height;
	titleSprite.setPosition(m_windowSize.x / 2.0F - titleSpriteX / 2.0F, m_windowSize.y / 14.0F - titleSpriteY / 2.0F);
}

float Window::SetDefaultScale(sf::Vector2u& windowSize)
{
	if (windowSize.x / WIDTH > windowSize.y / HEIGHT)
		return (float)(windowSize.y) / HEIGHT;
	return (float)(windowSize.x) / WIDTH;
}

void Window::SetArrowButton(sf::Sprite& arrowSprite, sf::Texture& arrowTexture, const std::string& arrowPath, bool arrowPos)
{
	arrowTexture.loadFromFile(arrowPath);
	arrowSprite.setTexture(arrowTexture);

	float scale = DEFAULT_SCALE / 8.0F;
	arrowSprite.setScale(scale, scale);

	float arrowSpriteX = arrowSprite.getGlobalBounds().width,
			arrowSpriteY = arrowSprite.getGlobalBounds().height;

	if(arrowPos)
		arrowSprite.setPosition(20.2F * m_windowSize.x / 21.0F - arrowSpriteX / 2.0F, m_windowSize.y / 15.0F - arrowSpriteY / 2.0F);
	else
		arrowSprite.setPosition(0.8F * m_windowSize.x / 21.0F - arrowSpriteX / 2.0F, m_windowSize.y / 15.0F - arrowSpriteY / 2.0F);
}

bool Window::MakeClickable(sf::Sprite& button, const sf::Vector2i& mousePos)
{
	float buttonWidth = button.getLocalBounds().width;
	float buttonHeight = button.getLocalBounds().height;

	if (mousePos.x > button.getGlobalBounds().left &&
		mousePos.x < button.getGlobalBounds().left + button.getGlobalBounds().width && mousePos.y > button.getGlobalBounds().top && 
		mousePos.y < (button.getGlobalBounds().top + button.getGlobalBounds().height))
	{
		button.setColor(sf::Color::Cyan);
		return true;
	}
	button.setColor(sf::Color::White);
	return false;
}

bool Window::MakeBiggerHover(sf::RenderWindow& window, sf::Sprite& button, const sf::Vector2i& mousePos)
{
	if (button.getGlobalBounds().width > button.getGlobalBounds().height)
		button.setScale(DEFAULT_SCALE / 4.6F, DEFAULT_SCALE / 4.1F);
	else
		button.setScale(DEFAULT_SCALE / 3.0F, DEFAULT_SCALE / 3.1F);

	if (mousePos.x > button.getGlobalBounds().left &&
		mousePos.x < button.getGlobalBounds().left + button.getGlobalBounds().width && mousePos.y > button.getGlobalBounds().top && 
		mousePos.y < (button.getGlobalBounds().top + button.getGlobalBounds().height))
	{
		button.setOrigin(button.getGlobalBounds().width, button.getGlobalBounds().height);
		button.scale(1.5, 1.5);
		window.draw(button);

		return true;
	}

	button.setOrigin(0, 0);
	button.scale(1, 1);
	window.draw(button);

	return false;
}

void Window::SetLogo(sf::Sprite& logoSprite, sf::Texture& logoTexture, const std::string& logoPath)
{
	logoTexture.loadFromFile(logoPath);
	logoSprite.setTexture(logoTexture);
	sf::Vector2u currentTextureSize = logoTexture.getSize();

	float scale = float(m_windowSize.x) / 5500;
	logoSprite.setScale(scale, scale);

	float logoX = logoSprite.getGlobalBounds().width,
		logoY = logoSprite.getGlobalBounds().height;
	logoSprite.setPosition(m_windowSize.x / 2.0F - logoX / 2, m_windowSize.y / 2.0F - logoY * scale * 4);
}
