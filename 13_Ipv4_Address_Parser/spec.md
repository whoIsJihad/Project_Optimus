## Correct Input
- Trim leading/trailing whitespace.
- Require exactly one :, splitting into address-part and port-part, both non-empty.
- Address-part: require exactly three ., four non-empty pieces, all-digit, no leading zero unless the piece is just "0", value 0–255.
- Port-part: all-digit, non-empty, value 0–65535.
- No characters left unconsumed anywhere.