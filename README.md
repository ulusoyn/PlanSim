# Planet Simulator - Physics & Units

## 🌍 Unit Convention (Normalized)
To ensure floating-point stability and visual clarity, this simulation does **not** use raw SI units (meters/kilograms). Instead, it uses a normalized system based on Earth's physical properties.

### The "Earth Standard"
| Quantity | Simulation Value | Real World Equivalent | Notes |
| :--- | :--- | :--- | :--- |
| **Mass** | `1.0` | $5.97 \times 10^{24}$ kg | 1 Earth Mass |
| **Distance** | `1.0` | $6,371$ km | 1 Earth Radius |
| **Time** | `1.0` | Variable | Depends on game speed |
| **G (Gravity)**| `10.0` | N/A | Tuned for visual pacing |

### Why these numbers?
Standard `float` variables lose precision with very large numbers (like $10^{24}$). By normalizing Earth to `1.0`, we keep all calculations near the "Floating Point Sweet Spot" ($0.001$ to $10,000$).

### Quick Reference
* **Sun Mass:** ~333,000.0 (333k Earths)
* **Moon Mass:** ~0.012 (1.2% Earth)
* **Moon Distance:** ~60.0 (60 Earth Radii)