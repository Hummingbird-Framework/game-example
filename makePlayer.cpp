#include "makeObjects.h"
#include <iostream>

void makePlayer(hb::GameObject* player, const Tmx::Map* map, int obj_grp, int obj_id)
{
	// Get Tmx object representing the new Player GameObject
	const Tmx::Object* obj = map->GetObjectGroup(obj_grp)->GetObject(obj_id);

	// Define GameObject status data and instantiate it
	struct Data
	{
		hb::Vector2d direction; //new hb::Vector2d());
		hb::Vector2d last_direction; //new hb::Vector2d(0, -1));
		bool running; //false);
		hb::SpriteComponent* player_sprite; //player->getComponent<hb::SpriteComponent>());
		bool is_grounded = false;
		unsigned int grounded_sensor_id;
		std::set<std::string> obstacles;
	};
	Data* data = new Data;

	b2BodyDef body_def;
	body_def.type = b2_dynamicBody;
	body_def.position = b2Vec2(player->getPosition().x, player->getPosition().y-1);
	body_def.fixedRotation = true;
	auto rigid_body = new hb::RigidBody2dComponent(body_def);
	// Define the player GameObject
	player->addComponents({
		new hb::SpriteComponent(),
		rigid_body,
		new hb::FunctionComponent()
	});
	hb::Material2d mat;
	mat.friction = obj->GetProperties().GetFloatProperty("friction", 0.);
	mat.bounciness = obj->GetProperties().GetFloatProperty("bounciness", 0.);
	mat.density = obj->GetProperties().GetFloatProperty("density", 1.);
	hb::BoxCollider2d collider(
		mat,
		hb::Vector2d(1,0.97),
		hb::Vector2d(0, -0.03),
		0.,
		false);

	rigid_body->addCollider(collider);

	hb::BoxCollider2d grounded_sensor(
		mat,
		hb::Vector2d(0.95, 0.1),
		hb::Vector2d(0, 0.5),
		0.,
		true);

	data->grounded_sensor_id = rigid_body->addCollider(grounded_sensor);

	// get the FunctionComponent we added in the definition
	auto fc = player->getComponent<hb::FunctionComponent>();

	// run initialization code (define variables and event callbacks)
	data->direction      = hb::Vector2d();
	data->last_direction = hb::Vector2d(1, 0);
	data->player_sprite  = player->getComponent<hb::SpriteComponent>();

	std::stringstream ss;
	ss << obj->GetProperties().GetStringProperty("obstacles");
	std::string tmp;
	while (ss >> tmp)
	{
		data->obstacles.insert(tmp);
	}

	hb::Texture tex = hb::Texture::loadFromFile("res/drawable/walking-tiles.png", hb::Rect(96, 128, 96, 128));
	hb::Sprite sprite = hb::Sprite(tex, hb::Vector2d(32, 32), hb::Vector2d());
	sprite.setCenter(hb::Vector2d(16, 16));

	data->player_sprite->setSprite(sprite);
	data->player_sprite->setScale(hb::Vector3d(0.5, 0.5, 0.5));
	data->player_sprite->setFrameOrder({6, 7, 8, 7});
	data->player_sprite->setFrameTime(hb::Time::seconds(0.1));


	// define update function
	fc->addListener("update", [=](hb::DataRepository&)
	{
		if (data->direction.y > 10.)
			data->direction.y = 10.;

		if (data->direction.x == 0)
			data->player_sprite->stop();
		else
			data->player_sprite->play();

		//hb::Renderer::getCamera().setPosition(player->getPosition());
	});


	fc->addListener("sensorStart", [=](hb::DataRepository& collision)
	{
		if (collision.getPointer<hb::Fixture2dData>("fixtureData")->id == data->grounded_sensor_id)
			data->is_grounded = true;
	});

	fc->addListener("sensorEnd", [=](hb::DataRepository& collision)
	{
		hb_log("sensorEnd: " << collision.getPointer<hb::Fixture2dData>("fixtureData")->id);
		if (collision.getPointer<hb::Fixture2dData>("fixtureData")->id == data->grounded_sensor_id)
			data->is_grounded = false;
	});

	// Define input listeners
	hb::InputManager::ListenerId<hb::KeyPressed> keypressed_listener_id = hb::InputManager::ListenerId<hb::KeyPressed>();
	hb::InputManager::ListenerId<hb::KeyReleased> keyreleased_listener_id = hb::InputManager::ListenerId<hb::KeyReleased>();
	keypressed_listener_id = hb::InputManager::instance()->listen(
	[=](hb::KeyPressed& event)
	{
		int value = 200./32.;

		hb::Keyboard::Key code = event.code;
		if (code == hb::Keyboard::Key::W)
		{
			if (data->is_grounded)
			{
				b2Vec2 v = rigid_body->getB2Body()->GetLinearVelocity();
				v.y = -7;
				rigid_body->getB2Body()->SetLinearVelocity(v);
				data->direction.y = -7;
			}
		}
		else if (code == hb::Keyboard::Key::A and data->direction.x >= 0)
		{
			b2Vec2 v = rigid_body->getB2Body()->GetLinearVelocity();
			v.x = -value;
			rigid_body->getB2Body()->SetLinearVelocity(v);
			data->direction.x = -value;
			data->last_direction = data->direction;
			data->player_sprite->setFrameOrder({3, 4, 5, 4});
		}
		else if (code == hb::Keyboard::Key::D and data->direction.x <= 0)
		{
			b2Vec2 v = rigid_body->getB2Body()->GetLinearVelocity();
			v.x = value;
			rigid_body->getB2Body()->SetLinearVelocity(v);
			data->direction.x = value;
			data->last_direction = data->direction;
			data->player_sprite->setFrameOrder({6, 7, 8, 7});
		}
		else if (code == hb::Keyboard::Key::Space)
		{
			/*auto bullet = makeBullet(hb::Vector2d(data->last_direction.x, 0));
			if (data->last_direction.x < 0)
				bullet->setPosition(player->getPosition() + hb::Vector3d(0,0.25,0));
			else
				bullet->setPosition(player->getPosition() + hb::Vector3d(0.5,0.25,0));
			*/
		}
	});
	keyreleased_listener_id = hb::InputManager::instance()->listen(
	[=](hb::KeyReleased& event)
	{
		hb::Keyboard::Key code = event.code;
		if (code == hb::Keyboard::Key::A and data->direction.x < 0)
		{
			b2Vec2 v = rigid_body->getB2Body()->GetLinearVelocity();
			v.x = 0;
			rigid_body->getB2Body()->SetLinearVelocity(v);
			data->direction.x = 0;
		}
		else if (code == hb::Keyboard::Key::D and data->direction.x > 0)
		{
			b2Vec2 v = rigid_body->getB2Body()->GetLinearVelocity();
			v.x = 0;
			rigid_body->getB2Body()->SetLinearVelocity(v);
			data->direction.x = 0;
		}
	});

	//define destructor function
	fc->addListener("destroy", [=](const hb::DataRepository&)
	{
		delete data;
		hb::InputManager::instance()->ignore(keypressed_listener_id);
		hb::InputManager::instance()->ignore(keyreleased_listener_id);
	});
}
