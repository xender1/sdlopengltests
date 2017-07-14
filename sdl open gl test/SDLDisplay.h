#pragma once

namespace Display {


	bool init();
	bool initGL();

	void close();
	bool isOpen();

	void clear();
	void render();

	void handleEvent();

}