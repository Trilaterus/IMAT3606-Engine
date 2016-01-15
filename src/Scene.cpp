#include "Scene.h"

Scene::Scene(std::string sFileName, GameObject* Camera, sf::RenderWindow& Window)
{
	if (Camera->hasCamera())
		m_pCamera = Camera;
	m_bIsMouseLocked = true;
	m_pWindow = &Window;

	tinyxml2::XMLDocument Scene;
	const char * cNamen = sFileName.c_str();
	if (Scene.LoadFile(cNamen))
	{
		std::cout << "Scene: Error opening XML file!" << std::endl;
	}

	// Go into <Scene>
	tinyxml2::XMLElement* eDoc = Scene.FirstChildElement("Scene");
	if (eDoc)
	{
		// Find first instance of <Object>
		tinyxml2::XMLElement* eObject = eDoc->FirstChildElement("Object");
		bool bParseObjs = true;
		while (bParseObjs)
		{
			// If an instance of <Object> is found...
			if (eObject)
			{
				GameObject* myGameObject = new GameObject;
				std::string sID;

				tinyxml2::XMLElement* eID = eObject->FirstChildElement("ID");
				// If an instance of <ID> is found...
				if (eID)
				{
					sID = eID->GetText();
				}
				else
				{
					std::cout << "Scene: Error, an <Object> has no <ID>!" << std::endl;
				}

				tinyxml2::XMLElement* eModel = eObject->FirstChildElement("Model");
				// If an instance of <Model> is found...
				if (eModel)
				{
					// Handle <OBJ>
					tinyxml2::XMLElement* eOBJ = eModel->FirstChildElement("OBJ");
					if (eOBJ)
					{
						std::string sOBJName = eOBJ->GetText();
						myGameObject->attachModel(sOBJName);
					}
					else
					{
						std::cout << "Scene: Error, a <Model> has no <OBJ>!" << std::endl;
					}

					// Handle <CamLock>
					tinyxml2::XMLElement* eCamLock = eModel->FirstChildElement("CamLock");
					if (eCamLock)
					{
						std::string sCamLock = eCamLock->GetText();
						// Even just writing <CamLock></CamLock> will enable it
						if (sCamLock != "f" ||
							sCamLock != "F" ||
							sCamLock != "false" ||
							sCamLock != "False")
						{
							myGameObject->setModelCamLock(true);
						}
					}

					// Handle <Position>
					tinyxml2::XMLElement* ePosition = eModel->FirstChildElement("Position");
					if (ePosition)
					{
						sf::Vector3f vfPosition;
						tinyxml2::XMLElement* eXPos = ePosition->FirstChildElement("x");
						if (eXPos)
						{
							std::string sX = eXPos->GetText();
							float fX = std::stof(sX);
							vfPosition.x = fX;
						}
						tinyxml2::XMLElement* eYPos = ePosition->FirstChildElement("y");
						if (eYPos)
						{
							std::string sY = eYPos->GetText();
							float fY = std::stof(sY);
							vfPosition.y = fY;
						}
						tinyxml2::XMLElement* eZPos = ePosition->FirstChildElement("z");
						if (eZPos)
						{
							std::string sZ = eZPos->GetText();
							float fZ = std::stof(sZ);
							vfPosition.z = fZ;
						}

						myGameObject->setModelPosition(vfPosition.x, vfPosition.y, vfPosition.z);
					}

					// Handle <Colour>
					tinyxml2::XMLElement* eColour = eModel->FirstChildElement("Colour");
					if (eColour)
					{
						sf::Vector3f vfColour = { 1.0, 1.0, 1.0 };
						tinyxml2::XMLElement* eR = eColour->FirstChildElement("r");
						if (eR)
						{
							std::string sR = eR->GetText();
							float fR = std::stof(sR);
							vfColour.x = fR;
						}
						tinyxml2::XMLElement* eG = eColour->FirstChildElement("g");
						if (eG)
						{
							std::string sG = eG->GetText();
							float fG = std::stof(sG);
							vfColour.y = fG;
						}
						tinyxml2::XMLElement* eB = eColour->FirstChildElement("b");
						if (eB)
						{
							std::string sB = eB->GetText();
							float fB = std::stof(sB);
							vfColour.z = fB;
						}

						myGameObject->setModelColour(vfColour.x, vfColour.y, vfColour.z);
					}

					// Handle <Angle>
					tinyxml2::XMLElement* eAngle = eModel->FirstChildElement("Angle");
					if (eAngle)
					{
						sf::Vector3f vfAngle;
						tinyxml2::XMLElement* eX = eAngle->FirstChildElement("x");
						if (eX)
						{
							std::string sX = eX->GetText();
							float fX = std::stof(sX);
							vfAngle.x = fX;
						}
						tinyxml2::XMLElement* eY = eAngle->FirstChildElement("y");
						if (eY)
						{
							std::string sY = eY->GetText();
							float fY = std::stof(sY);
							vfAngle.y = fY;
						}
						tinyxml2::XMLElement* eZ = eAngle->FirstChildElement("z");
						if (eZ)
						{
							std::string sZ = eZ->GetText();
							float fZ = std::stof(sZ);
							vfAngle.z = fZ;
						}

						myGameObject->setModelAngle(vfAngle.x, vfAngle.y, vfAngle.z);
					}
				}

				tinyxml2::XMLElement* eLight = eObject->FirstChildElement("Light");
				// If an instance of <Light> is found...
				if (eLight)
				{
					myGameObject->attachLight();

					// Handle <Position>
					tinyxml2::XMLElement* ePosition = eLight->FirstChildElement("Position");
					if (ePosition)
					{
						sf::Vector3f vfPosition;
						tinyxml2::XMLElement* eXPos = ePosition->FirstChildElement("x");
						if (eXPos)
						{
							std::string sX = eXPos->GetText();
							float fX = std::stof(sX);
							vfPosition.x = fX;
						}
						tinyxml2::XMLElement* eYPos = ePosition->FirstChildElement("y");
						if (eYPos)
						{
							std::string sY = eYPos->GetText();
							float fY = std::stof(sY);
							vfPosition.y = fY;
						}
						tinyxml2::XMLElement* eZPos = ePosition->FirstChildElement("z");
						if (eZPos)
						{
							std::string sZ = eZPos->GetText();
							float fZ = std::stof(sZ);
							vfPosition.z = fZ;
						}

						myGameObject->setLightPosition(vfPosition);
					}

					// Handle <Colour>
					tinyxml2::XMLElement* eColour = eLight->FirstChildElement("Diffuse");
					if (eColour)
					{
						sf::Vector3f vfColour = { 1.0, 1.0, 1.0 };
						tinyxml2::XMLElement* eR = eColour->FirstChildElement("r");
						if (eR)
						{
							std::string sR = eR->GetText();
							float fR = std::stof(sR);
							vfColour.x = fR;
						}
						tinyxml2::XMLElement* eG = eColour->FirstChildElement("g");
						if (eG)
						{
							std::string sG = eG->GetText();
							float fG = std::stof(sG);
							vfColour.y = fG;
						}
						tinyxml2::XMLElement* eB = eColour->FirstChildElement("b");
						if (eB)
						{
							std::string sB = eB->GetText();
							float fB = std::stof(sB);
							vfColour.z = fB;
						}

						myGameObject->setDiffuse(vfColour);
					}
					else
					{
						// If no colour is defined then set it to pure white
						myGameObject->setDiffuse(sf::Vector3f(1.0f, 1.0f, 1.0f));
					}
				}

				m_vGameObjects[sID] = myGameObject;

				eObject = eObject->NextSiblingElement("Object");
			}
			// If there are no more instances of <Object> in the XML file...
			else
			{
				// No more <Object>s left
				bParseObjs = false;
			}
		}

		// Find first instance of <UI>
		tinyxml2::XMLElement* eUI = eDoc->FirstChildElement("UI");
		bool bParseUI = true;
		while (bParseUI)
		{
			// If an instance of <UI> is found...
			if (eUI)
			{
				UIText* uiText = new UIText("", 0, 0); // TODO: Change to base class UI 
				std::string sID;

				tinyxml2::XMLElement* eID = eUI->FirstChildElement("ID");
				// If an instance of <ID> is found...
				if (eID)
				{
					sID = eID->GetText();
				}
				else
				{
					std::cout << "Scene: Error, a <UI> has no <ID>!" << std::endl;
				}

				tinyxml2::XMLElement* eText = eUI->FirstChildElement("Text");
				// If an instance of <Text> is found...
				if (eText)
				{
					//UIText* uiText = new UIText();

					tinyxml2::XMLElement* eString = eText->FirstChildElement("String");
					// Handle <String>
					if (eString)
					{
						std::string sString = eString->GetText();
						uiText->setString(sString);
					}

					tinyxml2::XMLElement* ePosition = eText->FirstChildElement("Position");
					// Handle <Position>
					if (ePosition)
					{
						sf::Vector2f vfPosition;
						tinyxml2::XMLElement* eX = ePosition->FirstChildElement("x");
						if (eX)
						{
							std::string sX = eX->GetText();
							float fX = std::stof(sX);
							vfPosition.x = fX;
						}
						tinyxml2::XMLElement* eY = ePosition->FirstChildElement("y");
						if (eY)
						{
							std::string sY = eY->GetText();
							float fY = std::stof(sY);
							vfPosition.y = fY;
						}

						uiText->setPosition(vfPosition);
					}
				}

				m_vUITexts[sID] = uiText;

				eUI = eUI->NextSiblingElement("UI");
			}
			// If there are no more instances of <UI> in the XML file...
			else
			{
				bParseUI = false;
			}
		}
	}
	else
	{
		std::cout << "Scene: XML may not be wrapped with <Scene> tag!" << std::endl;
	}

	// Turn on and update all the lights once (initialize)
	for (std::map<std::string, GameObject*>::const_iterator it = m_vGameObjects.begin()
		; it != m_vGameObjects.end(); ++it)
	{
		GameObject* myObject = it->second;
		if (myObject->hasLight())
		{
			myObject->updateLightAll();
		}
	}
}

void Scene::handleEvent(sf::Event sfEvent)
{
	sf::Vector2i WindowCentre = { (int)m_pWindow->getSize().x / 2, (int)m_pWindow->getSize().y / 2 };
	for (std::map<std::string, GameObject*>::const_iterator it = m_vGameObjects.begin()
		; it != m_vGameObjects.end(); ++it)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			m_pCamera->moveCameraForward(0.2f);

		// Change camera angle if mouse moves
		if (sfEvent.type == sf::Event::MouseMoved)
		{
			if (m_bIsMouseLocked)
			{
				if (sf::Mouse::getPosition(*m_pWindow) != WindowCentre)
				{
					float XDiff = sf::Mouse::getPosition(*m_pWindow).x - WindowCentre.x;
					float YDiff = sf::Mouse::getPosition(*m_pWindow).y - WindowCentre.y;
					float XAngle = (XDiff / WindowCentre.x) * 90; // 90 is sensitivity (180 would turn the character completely around by moving the mouse from one half of the screen to the other
					float YAngle = (YDiff / WindowCentre.y) * 90;
					m_pCamera->rotateCamera(YAngle, XAngle, 0.0f);
					sf::Mouse::setPosition(WindowCentre, *m_pWindow);
				}
			}
		}
	}
}

void Scene::update()
{
	for (std::map<std::string, GameObject*>::const_iterator it = m_vGameObjects.begin()
		; it != m_vGameObjects.end(); ++it)
	{
		GameObject* myObject = it->second;

		// Add commands for specific Models here
		if (it->first == "myMonkey")
			myObject->rotateModel(1.0f, 0.0f, 1.0f, 0.0f);

		if (myObject->hasModel())
			myObject->updateModel(*m_pWindow);
	}
}

void Scene::draw()
{
	sf::Vector3f vfCamAngle = m_pCamera->getCameraAngle();
	sf::Vector3f vfCamPos = m_pCamera->getCameraPosition();

	for (std::map<std::string, GameObject*>::const_iterator it = m_vGameObjects.begin()
		; it != m_vGameObjects.end(); ++it)
	{
		GameObject* myObject = it->second;
		if (myObject->hasLight())
		{
			myObject->updateLightPos(vfCamAngle, vfCamPos);
		}

		if (myObject->hasModel())
		{
			myObject->drawModel(vfCamAngle, vfCamPos);
		}
	}
}