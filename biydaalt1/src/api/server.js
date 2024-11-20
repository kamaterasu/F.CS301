const express = require("express");
const cors = require("cors");
const fs = require("fs");
const Nodehun = require("nodehun");

const app = express();
app.use(express.json()); // Parse JSON in requests
app.use(cors()); // Enable Cross-Origin Resource Sharing

// Load Hunspell dictionary files
const affPath = "./mn_MN.aff"; // Replace with your .aff file path
const dicPath = "./mn_MN.dic"; // Replace with your .dic file path

const affBuffer = fs.readFileSync(affPath);
const dicBuffer = fs.readFileSync(dicPath);

// Initialize Nodehun dictionary
const dictionary = new Nodehun(affBuffer, dicBuffer);

function isEnglishWord(word) {
  return /^[a-zA-Z]+$/.test(word);
}

function preprocessText(text) {
  return text
    .replace(/[^\w\s-]/g, "") // Remove all non-word characters except hyphen (-)
    .replace(/\s+/g, " ") // Replace multiple spaces with a single space
    .trim(); // Trim leading/trailing whitespace
}

/**
 * Checks the spelling of each word in a paragraph.
 * - Splits the paragraph into individual words after preprocessing.
 * - Checks each word against the dictionary.
 * - Returns a list of misspelled words with their details.
 */
async function checkParagraph(paragraph) {
  const cleanedText = preprocessText(paragraph); // Clean and normalize text
  const words = cleanedText.split(/\s+/); // Split text into words
  const results = [];

  for (const word of words) {
    if (isEnglishWord(word)) {
      continue; // Skip English words
    }

    const isCorrect = await dictionary.spell(word);
    if (!isCorrect) {
      results.push({ word, isCorrect }); // Add misspelled words to results
    }
  }

  return results;
}

// Endpoint to check spelling of a text input
app.post("/check-text", async (req, res) => {
  const { text } = req.body;

  // Validate input
  if (!text) {
    return res.status(400).json({ error: "No text provided" });
  }

  try {
    // Process the text and check spelling
    const misspelledWords = await checkParagraph(text);
    res.json({ text, misspelledWords }); // Return results
  } catch (error) {
    res.status(500).json({
      error: "Error processing text",
      details: error.message,
    });
  }
});

// Start the server
const PORT = 3000;
app.listen(PORT, () =>
  console.log(`Server is running on http://localhost:${PORT}`)
);
