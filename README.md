# OLPI - Octane's Linux Process Injector

A simple Linux Process Injector written in C as a learning project to understand process memory, pointers and low-level OS APIs.

> **LEGAL WARNING**
>
> This project was made at 3 AM with a lot of coffee and energy drinks for educational purposes only, not to provide a tool to Elliot Alderson Wannabes.
>
> Process injection can be used for both legitimate security research and malicious activities (blackhat), which i don't endorse in any way.

## Build

This assumes you have `gcc` and `make` installed. 

In your terminal:

```bash
gcc src/olpi.c src/banner.c -o olpi
```

## Usage

```bash
./olpi
```

**Note:** as of now, attaching to a process you don't own will fail with a permission error unless you run as root.

## Disclaimer

Use this only in your own environment, VMs, or authorized security labs.

