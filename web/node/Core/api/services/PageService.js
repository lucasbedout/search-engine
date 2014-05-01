// service page.js - Page manipulation fonctions


exports.stringToPage = function(entry) {

	function parseSingle(input)
    {
        var parts = input.split(';'),
            part,
            record = {};

        for (var i=0; i<parts.length; i++)
        {
            part = parts[i].split(',');
            record[part[0]] = part[1];
        }

        return record;
    }

    var parts = entry.split('|'),
        records = [];

    for (var i=0; i<parts.length; i++)
    {
        records.push(parseSingle(parts[i]));
    }

    return records;


};
