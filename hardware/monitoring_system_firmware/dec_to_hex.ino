void decimalToHexAndSplit(unsigned int decimalValue, unsigned char* upper, unsigned char* lower) {
  // Convert decimal to hex
  char hexString[5];  // Assuming a 16-bit decimal value
  sprintf(hexString, "%04X", decimalValue);

  // Parse hex string to get upper and lower parts
  sscanf(hexString, "%2hhX%2hhX", upper, lower);
}
