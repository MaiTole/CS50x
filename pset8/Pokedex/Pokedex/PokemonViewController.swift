import UIKit

class PokemonViewController: UIViewController {
    var url: String!
    var name: String!
    var id: Int!

    @IBOutlet var nameLabel: UILabel!
    @IBOutlet var numberLabel: UILabel!
    @IBOutlet var type1Label: UILabel!
    @IBOutlet var type2Label: UILabel!
    @IBOutlet var catchButton: UIButton!
    @IBOutlet var pokeImage: UIImageView!
    @IBOutlet var flavorText: UITextView!

    func capitalize(text: String) -> String {
        return text.prefix(1).uppercased() + text.dropFirst()
    }

    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)

        nameLabel.text = ""
        numberLabel.text = ""
        type1Label.text = ""
        type2Label.text = ""

        loadPokemon()
        initCatchStatus()
    }
    @IBAction func toggleCatch() {
        if UserDefaults.standard.object(forKey: self.name) == nil {
            UserDefaults.standard.set(true, forKey: self.name)
            catchButton.setTitle("Release!", for: UIControlState.normal)
            return
        }
        UserDefaults.standard.removeObject(forKey: self.name)
        self.catchButton.setTitle("Catch!", for: UIControlState.normal)
    }
    func initCatchStatus() {
        if UserDefaults.standard.object(forKey: self.name) != nil {
            self.catchButton.setTitle("Release!", for: .normal)
        }
    }
    func loadPokemon() {
        URLSession.shared.dataTask(with: URL(string: url)!) { (data, response, error) in
            guard let data = data else {
                return
            }

            do {
                let result = try JSONDecoder().decode(PokemonResult.self, from: data)
                DispatchQueue.main.async {
                    self.navigationItem.title = self.capitalize(text: result.name)
                    self.nameLabel.text = self.capitalize(text: result.name)
                    self.numberLabel.text = String(format: "#%03d", result.id)
                    let imageData = try? Data(contentsOf: (URL(string: result.sprites.front_default)!)) //NEW
                    self.pokeImage.image = UIImage(data: imageData!) //NEW

                    for typeEntry in result.types {
                        if typeEntry.slot == 1 {
                            self.type1Label.text = typeEntry.type.name
                        }
                        else if typeEntry.slot == 2 {
                            self.type2Label.text = typeEntry.type.name
                        }
                    }
                }
            
                guard let urlFlavor = URL(string: "https://pokeapi.co/api/v2/pokemon-species/\(result.id)") else {
                    return
                }
                
                URLSession.shared.dataTask(with: urlFlavor) { (data, response, error) in
                    guard let data = data else {
                        return
                    }
                    do {
                        let flavorDescription = try JSONDecoder().decode(PokemonDescription.self, from: data)
                        DispatchQueue.main.async {
                            for flavor in flavorDescription.flavor_text_entries {
                                if flavor.language.name.contains("en") {
                                    self.flavorText.text = flavor.flavor_text
                                    return
                                }
                            }
                        }
                    }
                    catch let error {
                        print(error)
                    }
                    }.resume()
            
            }
            catch let error {
                print(error)
            }
        }.resume()
        
        
        }
    }
