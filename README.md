# Prompt Interval Adder

This repository contains the "Prompt Interval Adder", a C program designed to facilitate interval-based text addition. This tool is particularly useful for managing large text inputs with language models (LLMs), helping to circumvent the context length limitations by inserting prompts or reminders at regular intervals.

## Description

The `prompt_interval_adder` program processes large text files by inserting a specified text snippet (prompt) every 300 lines, or the next available blank line if the exact interval is not suitable. It outputs the modified segments into sequentially numbered files within a designated directory. This segmentation approach can be particularly helpful for training or feeding data to language models where maintaining context is crucial.

## Features

- **Automatic Text Segmentation**: Automatically divides a text file into smaller segments with inserted prompts.
- **Flexible Directory Handling**: Creates a new directory for output files if it doesn't already exist.
- **Robust Error Management**: Ensures reliable file operations with comprehensive error handling.

## Installation

Clone this repository to your machine using:

```bash
git clone https://github.com/<your-username>/prompt-interval-adder.git
