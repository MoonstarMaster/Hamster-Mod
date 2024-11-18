/**
 * Include the Geode headers.
 */
#include <Geode/Geode.hpp>
#include <Geode/binding/ButtonSprite.hpp>

/**
 * Brings cocos2d and all Geode namespaces to the current scope.
 */
using namespace geode::prelude;

/**
 * `$modify` lets you extend and modify GD's classes.
 * To hook a function in Geode, simply $modify the class
 * and write a new function definition with the signature of
 * the function you want to hook.
 *
 * Here we use the overloaded `$modify` macro to set our own class name,
 * so that we can use it for button callbacks.
 *
 * Notice the header being included, you *must* include the header for
 * the class you are modifying, or you will get a compile error.
 *
 * Another way you could do this is like this:
 *
 * struct MyMenuLayer : Modify<MyMenuLayer, MenuLayer> {};
 */
#include <Geode/modify/MenuLayer.hpp>
class $modify(MyMenuLayer, MenuLayer) {
	/**
	 * Typically classes in GD are initialized using the `init` function, (though not always!),
	 * so here we use it to add our own button to the bottom menu.
	 *
	 * Note that for all hooks, your signature has to *match exactly*,
	 * `void init()` would not place a hook!
	*/
	bool init() {
		/**
		 * We call the original init function so that the
		 * original class is properly initialized.
		 */
		if (!MenuLayer::init()) {
			return false;
		}

		/**
		 * You can use methods from the `geode::log` namespace to log messages to the console,
		 * being useful for debugging and such. See this page for more info about logging:
		 * https://docs.geode-sdk.org/tutorials/logging
		*/
		log::debug("Hello from my MenuLayer::init hook! This layer has {} children.", this->getChildrenCount());

		/**
		 * See this page for more info about buttons
		 * https://docs.geode-sdk.org/tutorials/buttons
		*/
		auto myButton = CCMenuItemSpriteExtra::create(
			CCSprite::create("hamster-button.png"_spr),
			this,

			/**
			 * Here we use the name we set earlier for our modify class.
			*/
			menu_selector(MyMenuLayer::onMyButton)
		);



		/**
		 * Here we access the `bottom-menu` node by its ID, and add our button to it.
		 * Node IDs are a Geode feature, see this page for more info about it:
		 * https://docs.geode-sdk.org/tutorials/nodetree
		*/
		auto menu = this->getChildByID("bottom-menu");
		menu->addChild(myButton);

		/**
		 * The `_spr` string literal operator just prefixes the string with
		 * your mod id followed by a slash. This is good practice for setting your own node ids.
		*/
		myButton->setID("my-button"_spr);

		/**
		 * We update the layout of the menu to ensure that our button is properly placed.
		 * This is yet another Geode feature, see this page for more info about it:
		 * https://docs.geode-sdk.org/tutorials/layouts
		*/
		menu->updateLayout();


		/**
		 * We return `true` to indicate that the class was properly initialized.
		 */
		return true;
	}

	/**
	 * This is the callback function for the button we created earlier.
	 * The signature for button callbacks must always be the same,
	 * return type `void` and taking a `CCObject*`.
	*/
	/**class NewLayer;
	class $modify(MyNewLayer, NewLayer) {};
	*/
	void onMyButton(CCObject*) {
		auto NewScene = CCScene::create();
		auto NewLayer = MenuLayer::create();
		NewScene->addChild(NewLayer);
		auto Director = CCDirector::get();
		Director->pushScene(NewScene);

		auto hamsterImage = CCSprite::create("Sad-Hamster.png"_spr);
		NewLayer->addChild(hamsterImage);
		hamsterImage->setPosition({ 284, 160 });
		hamsterImage->setScaleX(3.550);
		hamsterImage->setScaleY(2.825);
		auto Audio = FMODAudioEngine::sharedEngine();
		Audio->pauseAllMusic(false);
		Audio->playEffect("sadViolin.ogg"_spr);


		auto myMenu = CCMenu::create();
		myMenu->setID("back-button");
		myMenu->setPosition(0, 0);
		NewLayer->addChild(myMenu);

		auto BackArrow = CCMenuItemSpriteExtra::create(
			CCSprite::createWithSpriteFrameName("backArrowPlain_01_001.png"),
			NewLayer,
			menu_selector(MyMenuLayer::onBackButton)
		);
		myMenu->addChild(BackArrow);
		BackArrow->setPosition(20, 300);

	}

	void onBackButton(CCObject*) {
		log::debug("onBackButton called");
		auto Director = CCDirector::get();
		Director->popScene();
		auto Audio = FMODAudioEngine::sharedEngine();
		Audio->resumeAllMusic();
		Audio->stopAllEffects();
	}

};
