# Git Configuration (Setup Identity)

After installing Git, you need to set up your identity.  
This is required so Git can correctly label your commits.

---

## Why Git Config is needed

Every commit stores metadata like:
- author name
- email address

Without configuration, Git won’t know who made the changes.

---

## Set your name

```bash
git config --global user.name "Your Name"
```

Example:
```bash
git config --global user.name "John Doe"
```

---

## Set your email

```bash
git config --global user.email "youremail@example.com"
```

Example:
```bash
git config --global user.email "john@example.com"
```

---

> [!NOTE]
> Use the same email that you use on GitHub for consistency.

---

## Check current configuration

```bash
git config --list
```

This shows all Git settings including:
- name
- email
- other configs

---

## Where config is stored

- Global config → applies to all repositories
- Stored in system user profile

---

## Important idea

> Git config does NOT affect code — only identity metadata.

---

## Minimal setup workflow

```bash
git config --global user.name "Your Name"
git config --global user.email "your@email.com"
git config --list
```

---
