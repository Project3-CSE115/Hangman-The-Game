#include <stdio.h>
#include <string.h>

#define MAX_TRIES 6
#define MAX_WORDS 500
#define MAX_LEVELS 10
#define WORD_COUNT 10
#define MAX_THEMES 7
#define MAX_LENGTH 20

typedef struct {
    char *name;
    char *words[WORD_COUNT];
    char *hints[WORD_COUNT];
} Theme;

typedef struct {
    Theme themes[MAX_THEMES];
} Level;

Level levels[MAX_LEVELS];
int levelCount = 0;

void addLevel(const char *themeList[MAX_THEMES], const char *wordLists[MAX_THEMES][WORD_COUNT], const char *hintLists[MAX_THEMES][WORD_COUNT]) {
    if (levelCount >= MAX_LEVELS) {
        printf("\nLevel limit reached.\n");
        return;
    }

    for (int i = 0; i < MAX_THEMES; i++) {
        levels[levelCount].themes[i].name = strdup(themeList[i]);
        if (levels[levelCount].themes[i].name == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }

        for (int j = 0; j < WORD_COUNT; j++) {
            levels[levelCount].themes[i].words[j] = strdup(wordLists[i][j]);
            levels[levelCount].themes[i].hints[j] = strdup(hintLists[i][j]);

            if (levels[levelCount].themes[i].words[j] == NULL || levels[levelCount].themes[i].hints[j] == NULL) {
                printf("Memory allocation failed.\n");
                return;
            }
        }
    }

    levelCount++;
}

int main() {
    const char *themeList[MAX_THEMES] = {"FOOD", "ANIMAL", "OBJECT", "SPORT", "CITY"};

    const char *wordLists[MAX_THEMES][WORD_COUNT] = {
        {"APPLE", "BANANA", "MILK", "PEAR", "BREAD", "HAM", "CAKE", "PIE", "TEA", "COFFEE"},
        {"DOG", "CAT", "ANT", "BAT", "DEER", "BEAR", "DUCK", "GOAT", "COW", "SHEEP"},
        {"BELL", "CUP", "CHAIR", "PHONE", "LAMP", "BOOK", "CLOCK", "BAG", "SHOE", "GLASS"},
        {"FOOTBALL", "DANCE", "TENNIS", "CRICKET", "BASEBALL", "GOLF", "SWIMMING", "CYCLING", "CHESS", "BOXING"},
        {"NEW YORK", "LONDON", "PARIS", "TOKYO", "SYDNEY", "DHAKA", "ROME", "DUBAI", "MILAN", "DELHI"}
    };
    const char *hintLists[MAX_THEMES][WORD_COUNT] = {
        {"A fruit that keeps the doctor away", 
         "A yellow fruit loved by monkeys", 
         "A dairy product often added to tea or coffee", 
         "A green or brown fruit with a sweet taste", 
         "A staple food made from flour", 
         "A type of cured meat", 
         "A sweet baked dessert", 
         "A dessert with a crust and filling", 
         "A hot beverage made from leaves", 
         "A hot beverage made from beans"},

        {"Man's best friend", 
         "A common pet that purrs", 
         "A small insect that works in colonies", 
         "A flying mammal", 
         "A graceful forest animal with antlers", 
         "A large mammal found in forests", 
         "A water bird that quacks", 
         "A farm animal known for its milk", 
         "A farm animal that gives milk and beef", 
         "A wool-producing farm animal"},

        {"Rings when pressed", 
         "Used to drink liquids", 
         "Furniture to sit on", 
         "Used to make calls", 
         "Provides light in a room", 
         "Used for reading", 
         "Shows the time", 
         "Used to carry items", 
         "Worn on feet", 
         "Used to drink water"},
    
        {"A game played with a round ball and goals", 
         "A rhythmic activity performed to music", 
         "A racket sport played on a court", 
         "A bat-and-ball game popular in South Asia", 
         "A bat-and-ball game popular in the USA", 
         "A sport played on a course with clubs", 
         "A water-based activity", 
         "A two-wheeled activity", 
         "A board game of strategy", 
         "A combat sport with gloves"},
    
        {"The Big Apple", 
         "Capital of the United Kingdom", 
         "The City of Light", 
         "Capital of Japan", 
         "Famous for its Opera House", 
         "Capital of Bangladesh", 
         "The Eternal City", 
         "Known for its skyscrapers and luxury", 
         "Fashion capital of Italy", 
         "Capital of India"}
    };

    addLevel(themeList, wordLists, hintLists);

    const char *themeList[MAX_THEMES] = {"FOOD", "ANIMAL", "SPORT", "CITY", "COLOUR"};

    const char *wordLists[MAX_THEMES][WORD_COUNT] = {
        {"RAMEN", "HONEY", "YOGURT", "STEAK", "CHEESE", "CEREAL", "PANCAKE", "PUMPKIN", "CUCUMBER", "PINEAPPLE"},
        {"PANDA", "MOUSE", "ELEPHANT", "TIGER", "SHARK", "WOLF", "MONKEY", "SNAKE", "CAMEL", "FROG"},
        {"SOCCER", "JUDO", "HOCKEY", "RUGBY", "SKATING", "WRESTLING", "BADMINTON", "BOWLING", "FENCING", "VOLLEYBALL"},
        {"MILAN", "CAIRO", "TORONTO", "BANGKOK", "CHICAGO", "MANILA", "KARACHI", "BERLIN", "FLORENCE", "MADRID"},
        {"AQUA", "BEIGE", "GOLD", "GREY", "CYAN", "SILVER", "TEAL", "IVORY", "INDIGO", "LAVENDER"}
    };
    const char *hintLists[MAX_THEMES][WORD_COUNT] = {
        
        {"A Japanese noodle soup dish", 
         "A sweet substance made by bees", 
         "A creamy dairy product often eaten with fruits", 
         "A cut of meat, often grilled or fried", 
         "A dairy product used in sandwiches and pizzas", 
         "A breakfast food made from grains", 
         "A flat, round breakfast food often served with syrup", 
         "A large orange vegetable used in pies", 
         "A green vegetable often used in salads", 
         "A tropical fruit with spiky skin and sweet yellow flesh"},
    
        {"A black-and-white bear that eats bamboo", 
         "A small rodent often kept as a pet", 
         "A large mammal with a trunk", 
         "A striped big cat", 
         "A predatory fish with sharp teeth", 
         "A wild canine known for its howl", 
         "A primate that loves bananas", 
         "A legless reptile", 
         "A desert animal with a hump", 
         "An amphibian that hops and croaks"},
    
        {"A game played with a round ball and goals", 
         "A martial art originating from Japan", 
         "A sport played on ice or a field with a stick", 
         "A contact sport played with an oval ball", 
         "A sport performed on ice with blades", 
         "A combat sport involving grappling", 
         "A racket sport played on a court", 
         "A game played by rolling a ball to knock down pins", 
         "A sport involving swords and protective gear", 
         "A team sport played with a net and a ball"},
    
        {"A fashion capital in Italy", 
         "The capital of Egypt", 
         "A major Canadian city", 
         "The capital of Thailand", 
         "A windy city in the USA", 
         "The capital of the Philippines", 
         "A populous city in Pakistan", 
         "The capital of Germany", 
         "A historic city in Italy known for art", 
         "The capital of Spain"},
    
        {"A shade of blue-green", 
         "A pale brown color", 
         "A precious metal color", 
         "A neutral shade between black and white", 
         "A bright blue-green color", 
         "A shiny gray-white metal color", 
         "A dark greenish-blue color", 
         "A creamy white color", 
         "A deep blue-purple color", 
         "A pale purple color"},
    };

    addLevel(themeList, wordLists, hintLists);

    const char *themeList[MAX_THEMES] = {"TECH", "ANIMAL", "CHARACTER", "CITY", "MATHS"};

    const char *wordLists[MAX_THEMES][WORD_COUNT] = {
        {"CLOUD", "JAVA", "ROUTER", "PIXEL", "SERVER", "BROWSER", "PYTHON", "INTERNET", "HACK", "DATABASE"},
        {"OWL", "VULTURE", "CHAMELEON", "CROCODILE", "HIPPOPOTAMUS", "PORCUPINE", "TURTLE", "RABBIT", "JAGUAR", "DOLPHIN"},
        {"HARRY POTTER", "YODA", "BATMAN", "THOR", "FRODA", "IRON MAN", "SHERLOCK", "HULK", "LOKI", "DUMBLEDORE"},
        {"KYOTO", "OSAKA", "SEOUL", "LAGOS", "VIENNA", "SANTIAGO", "SACRAMENTO", "NAIROBI", "AGRA", "PERTH"},
        {"ALGEBRA", "CALCULUS", "GEOMETRY", "FRACTION", "RATIO", "ANGLE", "EQUATION", "FUNCTION", "STATISTICS", "PARALLEL"}
    };
    const char *hintLists[MAX_THEMES][WORD_COUNT] = {
        {"A virtual storage system", 
         "A popular programming language", 
         "A device that directs network traffic", 
         "A small unit of a digital image", 
         "A computer that provides data to other computers", 
         "A software application for accessing the web", 
         "A programming language named after a snake", 
         "A global network connecting millions of devices", 
         "An unauthorized attempt to access data", 
         "A structured collection of data"},
    
        {"A nocturnal bird known for its hooting sound", 
         "A large bird of prey with a bald head", 
         "A reptile that can change its color", 
         "A large reptile with a powerful bite", 
         "A large, semi-aquatic mammal", 
         "A spiny mammal that rolls into a ball for defense", 
         "A slow-moving reptile with a shell", 
         "A small mammal known for its long ears", 
         "A large cat found in rainforests", 
         "A highly intelligent marine mammal"},
    
        {"The boy who lived in the wizarding world", 
         "A wise Jedi master from Star Wars", 
         "A superhero who fights crime in Gotham City", 
         "The Norse god of thunder", 
         "A hobbit from The Lord of the Rings", 
         "A genius billionaire superhero in a suit", 
         "A brilliant detective from Baker Street", 
         "A green superhero with immense strength", 
         "The god of mischief from Norse mythology", 
         "The headmaster of Hogwarts School of Witchcraft and Wizardry"},
    
        {"A historic city in Japan known for its temples", 
         "A major city in Japan known for its food and culture", 
         "The capital of South Korea", 
         "The largest city in Nigeria", 
         "The capital of Austria", 
         "The capital of Chile", 
         "The capital of California, USA", 
         "The capital of Kenya", 
         "A historic city in India known for the Taj Mahal", 
         "A major city in Western Australia"},
    
        {"A branch of mathematics dealing with equations", 
         "A branch of mathematics involving limits and derivatives", 
         "A branch of mathematics dealing with shapes and sizes", 
         "A part of a whole expressed as a ratio", 
         "A comparison of two quantities", 
         "A measure of the space between two lines", 
         "A mathematical statement showing equality", 
         "A relation between inputs and outputs", 
         "A branch of mathematics dealing with data analysis", 
         "Two lines that never meet"}
    };

    addLevel(themeList, wordLists, hintLists);

    const char *themeList[MAX_THEMES] = {"SCIENCE", "HARRY POTTER", "BOOK TITLE", "COUNTRY", "MOVIE"};

    const char *wordLists[MAX_THEMES][WORD_COUNT] = {
        {"CHEMISTRY", "PHYSICS", "BIOLOGY", "BEAKER", "BOTANY", "GEOLOGY", "ATOM", "MOLECULE", "ELEMENT", "COMPOUND"},
        {"SNAPE", "RON", "WEASLEY", "NEVILLE", "GRYFFINDOR", "SLYTHERIN", "DOBBY", "LUPIN", "NIMBUS", "HAGRID"},
        {"MOBY DICK", "THE HOBBIT", "THE BOOK THIEF", "THE SHINING", "1984", "CATCH 22", "LITTLE WOMEN", "PRIDE AND PREJUDICE", "ROMEO JULIET", "THE ALCHEMIST"},
        {"ARGENTINA", "CHINA", "KOREA", "JAPAN", "THAILAND", "CANADA", "GERMANY", "RUSSIA", "GREECE", "COLOMBIA"},
        {"TITANIC", "AVATAR", "INCEPTION", "PARASITE", "FROZEN", "TOY STORY", "GLADIATOR", "LA LA LAND", "UP", "COCO"}
    };
    const char *hintLists[MAX_THEMES][WORD_COUNT] = {
        {"The study of matter and its interactions", 
         "The study of energy and forces", 
         "The study of living organisms", 
         "A container used in laboratories", 
         "The study of plants", 
         "The study of Earth's physical structure", 
         "The smallest unit of matter", 
         "A group of atoms bonded together", 
         "A pure substance made of one type of atom", 
         "A substance formed by combining two or more elements"},
    
        {"The potions master at Hogwarts", 
         "Harry's best friend with red hair", 
         "The last name of Harry's best friend", 
         "A brave and clumsy Gryffindor student", 
         "The house of bravery and courage", 
         "The house of cunning and ambition", 
         "A loyal house-elf", 
         "A werewolf and Defense Against the Dark Arts teacher", 
         "A type of broomstick used for flying", 
         "The half-giant gamekeeper at Hogwarts"},
    
        {"A novel about a white whale", 
         "A fantasy novel about a hobbit's journey", 
         "A story about a girl who steals books during WWII", 
         "A horror novel by Stephen King", 
         "A dystopian novel by George Orwell", 
         "A satirical novel about war", 
         "A classic novel about four sisters", 
         "A romantic novel by Jane Austen", 
         "A tragic love story by Shakespeare", 
         "A philosophical novel by Paulo Coelho"},
    
        {"A South American country known for tango", 
         "The most populous country in the world", 
         "A country divided into North and South", 
         "An island nation in East Asia", 
         "A Southeast Asian country known for its beaches", 
         "A North American country known for maple syrup", 
         "A European country known for its engineering", 
         "The largest country in the world", 
         "A European country known for its ancient history", 
         "A South American country known for coffee"},
    
        {"A romantic movie about a shipwreck", 
         "A sci-fi movie set on Pandora", 
         "A mind-bending thriller by Christopher Nolan", 
         "An Oscar-winning South Korean film", 
         "A Disney movie about a magical ice queen", 
         "A Pixar movie about toys coming to life", 
         "A historical epic about a Roman general", 
         "A musical romance set in Los Angeles", 
         "A Pixar movie about a house lifted by balloons", 
         "A Pixar movie about a boy and the Land of the Dead"},
    };

    addLevel(themeList, wordLists, hintLists);

    const char *themeList[MAX_THEMES] = {"HARRY POTTER", "MYTHOLOGY", "INVENTORS", "K-POP", "TV SHOW"};

    const char *wordLists[MAX_THEMES][WORD_COUNT] = {
        {"MARAUDER", "SNITCH", "RAVENCLAW", "HUFFLEPUFF", "SIRIUS", "MALFOY", "QUIDDITCH", "HONEYDUKES", "CRUCIO", "PETRIFICUS TOTALUS"},
        {"ZEUS", "POSEIDON", "ATHENA", "ARES", "DIONYSUS", "ODIN", "THOR", "ANUBIS", "RA", "HORUS"},
        {"EINSTEIN", "NEWTON", "MARIE CURIE", "GALILEO", "TESLA", "DARWIN", "HAWKING", "MENDLEEV", "PASTEUR", "BOHR"},
        {"BTS", "BLACKPINK", "TWICE", "EXO", "IVE", "STRAY KIDS", "SEVENTEEN", "RED VELVET", "ITZY", "AESPA"},
        {"FRIENDS", "BREAKING BAD", "STRANGER THINGS", "LUCIFER", "MODERN FAMILY", "HOUSE", "THE FLASH", "EUPHORIA", "GILMORE GIRLS", "GOSSIP GIRLS"}
    };
    const char *hintLists[MAX_THEMES][WORD_COUNT] = {
        {"A group of mischievous map creators", 
         "A golden ball used in Quidditch", 
         "The house of wit and learning", 
         "The house of loyalty and hard work", 
         "Harry's godfather", 
         "A cunning and ambitious wizarding family", 
         "A popular wizarding sport", 
         "A sweet shop in Hogsmeade", 
         "A curse that causes immense pain", 
         "A spell that paralyzes the target"},
    
        {"The king of the Greek gods", 
         "The Greek god of the sea", 
         "The Greek goddess of wisdom and war", 
         "The Greek god of war", 
         "The Greek god of wine and revelry", 
         "The Norse god of wisdom and magic", 
         "The Norse god of thunder", 
         "The Egyptian god of the afterlife", 
         "The Egyptian sun god", 
         "The Egyptian god of the sky"},
    
        {"The physicist who developed the theory of relativity", 
         "The mathematician who formulated the laws of motion", 
         "The scientist who discovered radioactivity", 
         "The astronomer who supported the heliocentric model", 
         "The inventor of the alternating current system", 
         "The naturalist who proposed the theory of evolution", 
         "The physicist who studied black holes", 
         "The chemist who created the periodic table", 
         "The scientist who developed pasteurization", 
         "The physicist who developed quantum theory"},
    
        {"A globally famous boy band from South Korea", 
         "A girl group known for 'Kill This Love'", 
         "A girl group known for 'Fancy'", 
         "A boy group known for their powerful performances", 
         "A girl group known for 'Love Dive'", 
         "A boy group known for 'God's Menu'", 
         "A boy group with 13 members", 
         "A girl group known for 'Psycho'", 
         "A girl group known for 'Dalla Dalla'", 
         "A girl group known for 'Next Level'"},
    
        {"A sitcom about six friends in New York", 
         "A drama about a chemistry teacher turned drug lord", 
         "A sci-fi show about kids in Hawkins, Indiana", 
         "A show about the devil running a nightclub", 
         "A sitcom about a dysfunctional family", 
         "A medical drama about a brilliant but flawed doctor", 
         "A superhero show about the fastest man alive", 
         "A teen drama about high school students", 
         "A show about a mother and daughter duo", 
         "A drama about the lives of wealthy teenagers"},
    };

    addLevel(themeList, wordLists, hintLists);
    return 0;
}
