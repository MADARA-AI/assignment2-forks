#!/usr/bin/env bash
# setup_ssh_key.sh - generate (or show) an ed25519 SSH key and print the public key for GitHub
# Usage: ./setup_ssh_key.sh
set -euo pipefail

KEY="$HOME/.ssh/id_ed25519"
PUB="$KEY.pub"

echo "== SSH key setup helper =="

if [[ -f "$KEY" ]]; then
  echo "Found existing key: $KEY"
  echo
  echo "Public key (copy this into GitHub → Settings → SSH and GPG keys → New SSH key):"
  echo "------------------------------------------------------------"
  cat "$PUB"
  echo "------------------------------------------------------------"
  if command -v xclip >/dev/null 2>&1; then
    xclip -selection clipboard "$PUB" && echo "(Public key copied to clipboard via xclip)"
  elif command -v wl-copy >/dev/null 2>&1; then
    wl-copy < "$PUB" && echo "(Public key copied to clipboard via wl-copy)"
  fi
  echo
  echo "If you want to create a new key instead, rename or remove $KEY and re-run this script."
  exit 0
fi

read -r -p "Email/label for key (for GitHub key title) [$(whoami)@$(hostname)]: " EMAIL
EMAIL=${EMAIL:-$(whoami)@$(hostname)}

# Ask for passphrase (optional)
read -r -s -p "Enter a passphrase (leave empty for no passphrase): " PASSPHRASE
echo
read -r -s -p "Confirm passphrase: " PASSPHRASE2
echo
if [[ "$PASSPHRASE" != "$PASSPHRASE2" ]]; then
  echo "Passphrases do not match. Aborting."
  exit 1
fi

if [[ -n "$PASSPHRASE" ]]; then
  SSH_KEYGEN_CMD=(ssh-keygen -t ed25519 -C "$EMAIL" -f "$KEY" -N "$PASSPHRASE")
else
  SSH_KEYGEN_CMD=(ssh-keygen -t ed25519 -C "$EMAIL" -f "$KEY" -N "")
fi

echo "Generating new ed25519 key at $KEY ..."
"${SSH_KEYGEN_CMD[@]}"

eval "$(ssh-agent -s)" >/dev/null
ssh-add "$KEY"

echo
echo "Public key (copy into GitHub → Settings → SSH and GPG keys → New SSH key):"
echo "------------------------------------------------------------"
cat "$PUB"
echo "------------------------------------------------------------"

if command -v xclip >/dev/null 2>&1; then
  xclip -selection clipboard "$PUB" && echo "(Public key copied to clipboard via xclip)"
elif command -v wl-copy >/dev/null 2>&1; then
  wl-copy < "$PUB" && echo "(Public key copied to clipboard via wl-copy)"
fi

echo
echo "Next steps:"
echo "1) Open https://github.com/settings/keys and add a new SSH key. Paste the public key above."
echo "2) Test the connection: ssh -T git@github.com"
echo "3) If you already cloned the repo via HTTPS, switch to SSH:"
echo "   git remote set-url origin git@github.com:MADARA-AI/assignment2-forks.git"
echo "4) Then git pull / git push will stop asking for username/password."