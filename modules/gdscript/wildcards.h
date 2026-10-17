#include "core/string/ustring.h"
#include "core/variant/dictionary.h"
#include "core/variant/variant.h"
#include "scene/gui/text_edit.h"
#include "editor/settings/editor_settings.h"
#include <vector>

using namespace std;


class Wildcards {

	public:
	static bool has(String value) {
		for (String element : keys()) {
			if (element == value) {
				return true;
			}
		}
		return false;
	}

	static vector<String> keys() {
		const vector<String> keys = {
			"end",
			//ADD MORE WILDCARDS HERE!
		};
		return keys;
	}

	static vector<String> editor_keys() {
		const vector<String> editor_keys = keys();
		for (String key : editor_keys) {
			key = "text_editor/theme/highlighting/wildcard/"+key;
		}
		return editor_keys;
	}

	static void parser(const String &source_code) {
		
		String source = source_code;
		PackedStringArray lines = source.split("\n", true);

		for (int index = 0; index < lines.size(); index++) {

			String line = lines.get(index);
			String key = line.strip_edges();
			
			if (has(key)) {
				lines.set(index, "");
			}

		}
		source = String("\n").join(lines);
	}

	static void highlight(TextEdit *text_edit, Dictionary &color_map, int index) {

		String line = text_edit->get_line(index);
		String key = line.strip_edges();

		if (Wildcards::has(key)) {

			Dictionary info;
			info["color"] = EDITOR_GET("text_editor/theme/highlighting/wildcard/"+key);
			color_map[line.find(key)] = info;
		}
	}

	
};

