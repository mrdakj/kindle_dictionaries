#include <string>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <range/v3/view.hpp>
#include <range/v3/action.hpp>

#define assertm(exp, msg) assert(((void)msg, exp))

namespace fs = std::filesystem;

void write_header(std::ostream & output) {
    output <<
    "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
    "<html xmlns:idx=\"www.mobipocket.com\" xmlns:mbp=\"www.mobipocket.com\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n"
    "  <body>\n"
    "    <mbp:pagebreak/>\n"
    "    <mbp:frameset>\n"
    "      <mbp:slave-frame display=\"bottom\" device=\"all\" breadth=\"auto\" leftmargin=\"0\" rightmargin=\"0\" bottommargin=\"0\" topmargin=\"0\">\n"
    "        <div align=\"center\" bgcolor=\"yellow\"/>\n"
    "        <a onclick=\"index_search()\">Dictionary Search</a>\n"
    "        </div>\n"
    "      </mbp:slave-frame>\n"
    "\n"
    "      <mbp:pagebreak/>\n";
}

void write_footer(std::ostream & output) {
    output <<
    "\n"
    "    </mbp:frameset>\n"
    "  </body>\n"
    "</html>\n";
}

void write_word(std::ostream & output, std::string source, std::string target) {
    output <<
    "\n"
    "      <idx:entry name=\"word\" scriptable=\"yes\">\n"
    "      <h2>\n"
    "      <idx:orth>"+ source + "</idx:orth><idx:key key=\"" + std::move(source) + "\">\n"
    "      </h2>\n"
    "          " + std::move(target) + "\n"
    "      </idx:entry>\n";
}

void generate_html()
{
    std::ofstream output("dictionary.html");
    write_header(output);

    std::string source_path = "source";
    std::vector<fs::directory_entry> source_words;
    std::copy(fs::directory_iterator(source_path), fs::directory_iterator(), std::back_inserter(source_words));
    std::sort(source_words.begin(), source_words.end());

    std::string target_path = "target";
    std::vector<fs::directory_entry> target_words;
    std::copy(fs::directory_iterator(target_path), fs::directory_iterator(), std::back_inserter(target_words));
    std::sort(target_words.begin(), target_words.end());

    assertm(source_words.size() == target_words.size(), "sizes mismatch");

    for (const auto& [source, target] : ranges::views::zip(source_words, target_words)) {
        std::ifstream source_input(source.path());
        std::ifstream target_input(target.path());

        auto s_range = ranges::getlines(source_input);
        auto t_range = ranges::getlines(target_input);

        for (auto&& [s, t] : ranges::views::zip(s_range, t_range)) {
             write_word(output, std::move(s), std::move(t));
        }
    }  

    write_footer(output);
}

void generate_opf(const std::pair<std::string, std::string>& lang) {
    std::ofstream output("dictionary.opf");

	output <<
	"<?xml version=\"1.0\"?><!DOCTYPE package SYSTEM \"oeb1.ent\">\n"
	"\n"
	"<package unique-identifier=\"uid\" xmlns:dc=\"Dublin Core\">\n"
	"\n"
	"<metadata>\n"
	"    <dc-metadata>\n"
	"        <dc:Identifier id=\"uid\">eng_" + lang.first + "</dc:Identifier>\n"
	"        <!-- Title of the document -->\n"
	"        <dc:Title><h2>english " + lang.second + " dictionary</h2></dc:Title>\n"
	"        <dc:Language>EN</dc:Language>\n"
	"    </dc-metadata>\n"
	"    <x-metadata>\n"
	"\n"
	"        <DictionaryInLanguage>en-us</DictionaryInLanguage>\n"
	"        <DictionaryOutLanguage>" + lang.second + "</DictionaryOutLanguage>\n"
	"    </x-metadata>\n"
	"</metadata>\n"
	"\n"
	"<!-- list of all the files needed to produce the .prc file -->\n"
	"<manifest>\n"
	" <item id=\"dictionary0\" href=\"dictionary.html\" media-type=\"text/x-oeb1-document\"/>\n"
	"<item href=\"cover.jpg\" id=\"my-cover-image\" media-type=\"image/jpeg\" />\n"
	"</manifest>\n"
	"\n"
	"\n"
	"<!-- list of the html files in the correct order  -->\n"
	"<spine>\n"
	"    <itemref idref=\"dictionary0\"/>\n"
	"</spine>\n"
	"\n"
	"<tours/>\n"
	"<!-- <guide> <reference type=\"search\" title=\"Dictionary Search\" onclick= \"index_search()\"/> </guide> -->\n"
	"</package>\n";
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: ./dictionary <languageKey> <language>" << std::endl;
        return 1;
    }
    generate_html();
	generate_opf({argv[1], argv[2]});
    return 0;
}
