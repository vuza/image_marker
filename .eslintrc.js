module.exports = {
    "env": {
        "browser": true,
        "es6": true,
        "node": true
    },
    globals: {
        "define": false,
        "Marionette": false,
        "$": false,
        "Backbone": false
    },
    "extends": "eslint:recommended",
    "rules": {
        "indent": [
            "error",
            4
        ],
        "linebreak-style": [
            "error",
            "unix"
        ],
        "quotes": [
            "error",
            "single"
        ],
        "semi": [
            "error",
            "always"
        ],
        "one-var": [
            "error",
            "never"
        ],
        "curly": [
            "error"
        ],
        "no-console": [
            "error",
            { allow: ["warn", "error"] }
        ]
    }
};