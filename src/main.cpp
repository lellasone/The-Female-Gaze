#include <SFML/Graphics.hpp>
#include <iostream>
#include <string> 
#include <thread>
#include <chrono>

#include "csv.h" // This is a library we downloaded. 


struct quote_entry
{
    std::string text;
    std::string author;
    int char_count = 0;
    std::string rating = "R"; // think "R" or "G"
    int censorship = 0;
    int domestic_sphere = 0;
    int sex_the_act = 0;
    int sexual_diversity = 0;
    int sex_the_catagory = 0;
    int language = 0;
    int rape_mention = 0;
    int violence = 0;
    int motivational = 0;
    int feminism = 0;
    std::string religion = "";
    int intersectionality = 0;
    int misandry = 0;
    int capitalism = 0;
    int controversial_author = 0;
    int wave = 0; // Which wave of feminism. 
    int author_birth_decade = 0;
};


int max_quote_width = 1500; // How big can the quote box be. 
int max_quote_height = 800; // how big can the quote box be. 
int main()
{


    // Import data from csv. 
    io::CSVReader<21, io::trim_chars<' '>, io::double_quote_escape<',','\"'>> in("resources/tfg_quotes.csv");
    in.read_header(io::ignore_extra_column,
                 "Text",
                 "Author",
                 "Character Count",
                 "Rating",
                 "Censorship", 
                 "Domestic Sphere", 
                 "Sex the act", 
                 "Sexual diversity", 
                 "Sex the category", 
                 "Language",
                 "Rape mention",
                 "Violence",
                 "Motivational",
                 "Feminism",
                 "Religion",
                 "Intersectionality",
                 "Misandry",
                 "Capitalism",
                 "Controversial Author",
                 "Wave",
                 "Decade of Author Birth");


    quote_entry temp;
    std::vector<quote_entry> quotes;
    while(in.read_row(temp.text,
                        temp.author,
                        temp.char_count,
                        temp.rating,
                        temp.censorship,
                        temp.domestic_sphere,
                        temp.sex_the_act,
                        temp.sexual_diversity,
                        temp.sex_the_catagory,
                        temp.language,
                        temp.rape_mention,
                        temp.violence,
                        temp.motivational,
                        temp.feminism,
                        temp.religion,
                        temp.intersectionality,
                        temp.misandry,
                        temp.capitalism,
                        temp.controversial_author,
                        temp.wave,
                        temp.author_birth_decade
                        ))
    {
        quote_entry entry = temp;
        // entry.text = Text;
        // entry.author = author;
        quotes.push_back(entry);
    }

    for (quote_entry& q : quotes)
    {
        std::cout << q.text << q.author << q.char_count << " " << temp.author_birth_decade << std::endl;
    }

    // Set up the SFML window. 
    double width = 1920;
    double height = 1080;

    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "SFML works!", sf::Style::Fullscreen);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);

    sf::Font font;
    if (!font.loadFromFile("resources/rouge-script/RougeScript-Regular.ttf"))
        return EXIT_FAILURE;

    
    int base_text_size = 200;
    sf::Text text(quotes[0].text, font, base_text_size);
    sf::Text author(quotes[0].author, font, base_text_size / 2);


    int count = 0;

    window.setMouseCursorVisible(false);

    while (window.isOpen())
    {

        // Select the quote. 
        std::string quote = "Hello World:";


        // Handle the video output. 
	    sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        // window.draw(shape)

        // Set up the text. 

        // Replace endline tokens with endlines and set text.
        std::string endl_standin = "\"/n\"";
        std::cout << "token: " << endl_standin << std::endl;

        int num_quotes = std::min(5, int(quotes.size()));
        int index = count % num_quotes;
        std::string quote_text = quotes[index].text;

        size_t endl_pos = quote_text.find(endl_standin);
        while (endl_pos != std::string::npos)
        {
            quote_text.replace(endl_pos, endl_standin.size(), "\n");
            endl_pos = quote_text.find(endl_standin);
        }
        
        

        // Resize quote as needed. 
        text.setString(quote_text);
        float scale = std::min({float(max_quote_width / text.getLocalBounds().width),
                                float(max_quote_height / text.getLocalBounds().height),
                                float(1.)});
        std::cout << "Quote Scale: " << scale << std::endl;
        text.setScale({scale, scale});
        text.setPosition({width * 0.5 - text.getLocalBounds().width/2 * scale, height * 0.5 - text.getLocalBounds().height/2 * scale});

        // Set up author position. 
        // As configured it should be half a line below the quote, and right justified. 
        author.setString( " - " + quotes[index].author);
        author.setScale({scale, scale});
        author.setPosition({text.getPosition().x+text.getLocalBounds().width*scale - author.getLocalBounds().width*scale,
                            text.getPosition().y + text.getLocalBounds().height*scale + text.getCharacterSize()*scale/2});

        std::cout << text.getLocalBounds().width << " " << text.getLocalBounds().height << std::endl;
        count ++;
        window.draw(text);
        window.draw(author);
        window.display();
        std::this_thread::sleep_for(std::chrono::seconds(60));
    }

    return 0;
}
