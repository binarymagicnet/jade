#include "sfml2.inc"

MAIN
    RenderWindow window(VideoMode(200, 200), "JADE SFML2!");
    CircleShape shape(100.f);
    shape.setFillColor(Color::Green);
    Font font;
    IF (!font.loadFromFile("data/ahronbd.ttf")) THEN
        RETURN EXIT_FAILURE;
    ENDIF
    Text text("JADE", font);
    text.setColor(Color(0, 100, 0, 200));
    text.setPosition(68.f, 77.f);
    WHILE (window.isOpen()) BEGIN
        Event event;
        WHILE (window.pollEvent(event)) BEGIN
            IF (event.type == Event::Closed) THEN
                window.close();
            ENDIF
        WEND
        window.clear();
        window.draw(shape);
        window.draw(text);
        window.display();
    WEND
    RETURN EXIT_SUCCESS;
END
